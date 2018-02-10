#include "listaproducto.h"

bool ListaProducto::agregar(NodoProducto *actual, NodoProducto *nuevo)
{
    if (actual->getItem()->comparar(nuevo->getItem()) > 0)
    {
        nuevo->setSiguiente(actual);
        actual->getAnterior()->setSiguiente(nuevo);
        nuevo->setAnterior(actual->getAnterior());
        actual->setAnterior(nuevo);

        return true;
    }

    if (actual->getItem()->comparar(nuevo->getItem()) == 0
            || actual->getAnterior()->getItem()->comparar(nuevo->getItem()) == 0)
        return false;

    return agregar(actual->getSiguiente(), nuevo);
}

NodoProducto *ListaProducto::buscar(NodoProducto *actual, QString value)
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

ListaProducto::ListaProducto()
{
    primero = ultimo = NULL;
}

ListaProducto::~ListaProducto()
{
    NodoProducto *temp = primero;
    if (temp == NULL)
        return;

    primero->setAnterior(NULL);
    ultimo->setSiguiente(NULL);

    while (temp != NULL)
    {
        primero = temp->getSiguiente();
        delete temp;
        temp = primero;
    }

    ultimo = NULL;
}

void ListaProducto::setPrimero(NodoProducto *value)
{
    primero = value;
}

NodoProducto *ListaProducto::getPrimero()
{
    return primero;
}

void ListaProducto::setUltimo(NodoProducto *value)
{
    ultimo = value;
}

NodoProducto *ListaProducto::getUltimo()
{
    return ultimo;
}

bool ListaProducto::vacio()
{
    return primero == NULL && ultimo == NULL;
}

bool ListaProducto::agregar(TADProducto *producto)
{
    NodoProducto *nuevo = new NodoProducto(producto);

    if (vacio()) {
        primero = ultimo = nuevo;
        primero->setAnterior(nuevo);
        ultimo->setSiguiente(nuevo);

        return true;
    }

    if (primero->getItem()->comparar(producto) > 0)
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        primero->setAnterior(nuevo);
        ultimo->setSiguiente(nuevo);
        primero = nuevo;

        return true;
    }

    if (producto->comparar(ultimo->getItem()) > 0)
    {
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(primero);
        ultimo->setSiguiente(nuevo);
        primero->setAnterior(nuevo);
        ultimo = nuevo;

        return true;
    }

    if (!agregar(primero->getSiguiente(), nuevo))
    {
        delete nuevo;
        nuevo = NULL;
        return false;
    }
    else
        return true;
}

NodoProducto *ListaProducto::buscar(QString value)
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

bool ListaProducto::eliminar(QString value)
{
    NodoProducto *nodo = buscar(value);

    if (nodo != NULL)
    {
        if (primero == nodo)
        {
            primero = primero->getSiguiente();
            primero->setAnterior(ultimo);
            ultimo->setSiguiente(primero);

            delete nodo;
            nodo = NULL;
            return true;
        }
        else
        {
            NodoProducto *anterior = nodo->getAnterior();
            anterior->setSiguiente(nodo->getSiguiente());

            if (ultimo == nodo)
            {
                primero->setAnterior(anterior);
                ultimo = anterior;
            }
            else
                nodo->getSiguiente()->setAnterior(anterior);

            delete nodo;
            nodo = NULL;
            return true;
        }
    }
    else
        return false;
}

void ListaProducto::graficar()
{
    NodoProducto *temp = primero;
    QFile file("listaProducto.dot");
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream out(&file);
    out << "digraph lista_producto {\n";
    out << "\trankdir = LR\n";
    out << "\tnode [shape = record]\n\n";
    out.flush();

    while (temp != NULL)
    {
        out << "\t" << temp->getItem()->getNombreNodo();
        out << " [label = \"" << temp->getItem()->toString();
        out << "\"];\n";
        out.flush();

        if (temp->getSiguiente() != NULL)
        {
            out << "\t" << temp->getItem()->getNombreNodo();
            out << " -> " << temp->getSiguiente()->getItem()->getNombreNodo();
            out << ";\n";
            out.flush();
        }

        if (temp->getAnterior() != NULL)
        {
            out << "\t" << temp->getItem()->getNombreNodo();
            out << " -> " << temp->getAnterior()->getItem()->getNombreNodo();
            out << ";\n";
            out.flush();
        }

        if (temp->getSiguiente() != primero)
            temp = temp->getSiguiente();
        else
            temp = NULL;
    }

    out << "}";
    out.flush();
    file.close();

    system("dot -Tpng -o listaProducto.png listaProducto.dot");
}

void ListaProducto::cargarDetalle(QTableWidget *table)
{
    if (!vacio())
    {
        NodoProducto *temp = primero;

        while (temp != NULL)
        {
            table->insertRow(table->rowCount());
            table->setItem(table->rowCount() - 1, CODIGO, new QTableWidgetItem(temp->getItem()->getCodigo()));
            table->setItem(table->rowCount() - 1, NOMBRE, new QTableWidgetItem(temp->getItem()->getNombre()));
            table->setItem(table->rowCount() - 1, PRECIO, new QTableWidgetItem(QString::number(temp->getItem()->getPrecio())));

            if (temp->getSiguiente() != primero)
                temp = temp->getSiguiente();
            else
                temp = NULL;
        }
    }
}
