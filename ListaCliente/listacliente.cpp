#include "listacliente.h"

bool ListaCliente::agregar(NodoCliente *anterior, NodoCliente *actual, NodoCliente *nuevo)
{
    if (actual->getItem()->comparar(nuevo->getItem()) == 0
        || anterior->getItem()->comparar(nuevo->getItem()) == 0)
        return false;

    if (actual->getItem()->comparar(nuevo->getItem()) > 0)
    {
        nuevo->setSiguiente(actual);
        anterior->setSiguiente(nuevo);

        return true;
    }

    return agregar(actual, actual->getSiguiente(), nuevo);
}

NodoCliente *ListaCliente::buscar(NodoCliente *actual, QString value)
{
    if (actual->getItem()->comparar(value) == 0)
        return actual;
    else
    {
        if (actual->getItem()->comparar(value) < 0)
            return buscar(actual->getSiguiente(), value);
        else
            return NULL;
    }
}

NodoCliente *ListaCliente::buscarAnterior(NodoCliente *actual, QString value)
{
    if (actual->getSiguiente()->getItem()->comparar(value) == 0)
        return actual;
    else
    {
        if (actual->getSiguiente()->getItem()->comparar(value) < 0)
            return buscarAnterior(actual->getSiguiente(), value);
        else
            return NULL;
    }
}

bool ListaCliente::transpasarFacturas(NodoCliente *origen)
{
    NodoCliente *destino = NULL;

    agregar(new TADCliente("0", "CF"));
    destino = buscar("0");

    destino->getItem()->agregarFacturas(origen->getItem()->getFacturas());
    origen->getItem()->setFactura(NULL);

    return true;
}

ListaCliente::ListaCliente()
{
    primero = ultimo = NULL;
}

ListaCliente::~ListaCliente()
{
    NodoCliente *temp = primero;

    while (temp != NULL)
    {
        primero = temp->getSiguiente();
        delete temp;
        temp = primero;
    }

    ultimo = NULL;
}

void ListaCliente::setPrimero(NodoCliente *value)
{
    primero = value;
}

NodoCliente *ListaCliente::getPrimero()
{
    return primero;
}

void ListaCliente::setUltimo(NodoCliente *value)
{
    ultimo = value;
}

NodoCliente *ListaCliente::getUltimo()
{
    return ultimo;
}

bool ListaCliente::vacio()
{
    return primero == NULL;
}

bool ListaCliente::agregar(TADCliente *cliente)
{
    if (vacio())
    {
        primero = ultimo = new NodoCliente(cliente);;

        return true;
    }

    if (primero->getItem()->comparar(cliente) > 0)
        return agregarPrimero(cliente);

    if (cliente->comparar(ultimo->getItem()) > 0)
        return agregarUltimo(cliente);

    NodoCliente *nuevo = new NodoCliente(cliente);
    if (!agregar(primero, primero->getSiguiente(), nuevo))
    {
        delete nuevo;
        nuevo = NULL;
        return false;
    }
    else
        return true;
}

bool ListaCliente::actualizar(QString _nit, TADCliente *cliente)
{
    if (cliente->comparar(_nit) != 0)
    {
        NodoCliente *temp = buscar(primero, cliente->getNit());

        if (contar() == 1)
        {
            cliente->setNit(_nit);
            return true;
        }

        if (primero == temp)
            primero = temp->getSiguiente();
        else
        {
            NodoCliente *anterior = buscarAnterior(primero, cliente->getNit());
            anterior->setSiguiente(temp->getSiguiente());

            if (temp == ultimo)
                ultimo = anterior;
        }

        temp->setSiguiente(NULL);
        cliente->setNit(_nit);

        if (primero->getItem()->comparar(_nit) > 0)
        {
            temp->setSiguiente(primero);
            primero = temp;

            return true;
        }
        if (ultimo->getItem()->comparar(_nit) < 0)
        {
            ultimo->setSiguiente(temp);
            ultimo = temp;

            return true;
        }

        return agregar(primero, primero->getSiguiente(), temp);
    }
    else
        return true;

}

bool ListaCliente::agregarPrimero(TADCliente *cliente)
{
    NodoCliente *nuevo = new NodoCliente(cliente);

    if (!vacio())
    {
        nuevo->setSiguiente(primero);
        primero = nuevo;

        return true;
    }

    primero = ultimo = nuevo;

    return true;
}

bool ListaCliente::agregarUltimo(TADCliente *cliente)
{
    NodoCliente *nuevo = new NodoCliente(cliente);

    if (!vacio())
    {
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;

        return true;
    }

    primero = ultimo = nuevo;

    return true;
}

NodoCliente *ListaCliente::buscar(QString value)
{
    if (!vacio())
    {
        if (primero->getItem()->comparar(value) < 0
                && ultimo->getItem()->comparar(value) > 0)
            return buscar(primero, value);
        else
        {
            if (primero->getItem()->comparar(value) == 0)
                return primero;
            if (ultimo->getItem()->comparar(value) == 0)
                return ultimo;

            return NULL;
        }
    }
    else
        return NULL;
}

TADCliente *ListaCliente::obtener(QString value)
{
    NodoCliente *nodo = buscar(value);
    if (nodo != NULL)
        return nodo->getItem();
    else
        return NULL;
}

bool ListaCliente::eliminar(QString value)
{
    if (value.compare("0") == 0)
        return false;

    if (contar() == 1)
    {
        if (primero->getItem()->comparar(value) == 0)
        {
            transpasarFacturas(primero);
            delete primero;
            primero = ultimo = NULL;

            return true;
        }
        else
            return false;
    }
    else
    {
        NodoCliente *nodo = buscar(value);

        if (nodo != NULL)
        {
            if (primero == nodo)
                primero = primero->getSiguiente();
            else
            {
                NodoCliente *anterior = buscarAnterior(primero, value);
                anterior->setSiguiente(nodo->getSiguiente());

                if (ultimo == nodo)
                    ultimo = anterior;
            }

            transpasarFacturas(nodo);
            delete nodo;
            nodo = NULL;
            return true;
        }
        else
            return false;
    }
}

void ListaCliente::graficar()
{
    NodoCliente *temp = primero;
    QFile file("listaCliente.dot");
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream out(&file);
    out << "digraph lista_cliente {\n";
    out << "\trankdir = LR\n";
    out << "\tnode [shape = record]\n\n";
    out.flush();

    while (temp != NULL)
    {
        out << "\t" << temp->getItem()->getNombreNodo();
        out << " [label = \"" << temp->getItem()->toString() << "\"]\n";
        out.flush();

        if (temp->getSiguiente() != NULL)
        {
            out << "\t" << temp->getItem()->getNombreNodo();
            out << " -> " << temp->getSiguiente()->getItem()->getNombreNodo();
            out << ";\n";
            out.flush();
        }

        temp = temp->getSiguiente();
    }

    out << "}";
    out.flush();
    file.close();

    system("dot -Tpng -o listaCliente.png listaCliente.dot");
    system("eog listaCliente.png");

    std::cout << "Creación de grafo completado" << std::endl;
}


void ListaCliente::cargarDetalle(QTableWidget *table)
{
    if (!vacio())
    {
        NodoCliente *temp = primero;

        while (temp != NULL)
        {
            table->insertRow(table->rowCount());
            table->setItem(table->rowCount() - 1, NIT, new QTableWidgetItem(temp->getItem()->getNit()));
            table->setItem(table->rowCount() - 1, NOMBRE, new QTableWidgetItem(temp->getItem()->getNombre()));

            temp = temp->getSiguiente();
        }
    }
}

int ListaCliente::contar()
{
    int i = 0;

    NodoCliente *temp = primero;

    while (temp != NULL)
    {
        i++;
        temp = temp->getSiguiente();
    }

    return i;
}
