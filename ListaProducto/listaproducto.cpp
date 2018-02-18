#include "listaproducto.h"

bool ListaProducto::agregar(NodoProducto *actual, NodoProducto *nuevo)
{
    if (actual->getItem()->comparar(nuevo->getItem()) == 0
            || actual->getAnterior()->getItem()->comparar(nuevo->getItem()) == 0)
        return false;

    if (actual->getItem()->comparar(nuevo->getItem()) > 0)
    {
        nuevo->setSiguiente(actual);
        actual->getAnterior()->setSiguiente(nuevo);
        nuevo->setAnterior(actual->getAnterior());
        actual->setAnterior(nuevo);

        return true;
    }

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

TADProducto *ListaProducto::busquedaBinaria(int a, int b, NodoProducto *nodo_a, NodoProducto *nodo_b, QString value)
{
    int m = 0;
    m = (b - a) / 2;

    NodoProducto *nodo_m;
    nodo_m = nodo_a;

    for (int i = 0; i <= m; i++)
        nodo_m = nodo_m->getSiguiente();

    qDebug() << "*********************************************" << endl;
    qDebug() << "Encontrar: " << value << endl;
    qDebug() << "---------------------------------------------" << endl;
    qDebug() << "Extremo a: " << nodo_a->getItem()->getCodigo() << endl;
    qDebug() << "Medio: " << nodo_m->getItem()->getCodigo() << endl;
    qDebug() << "Extremo b: " << nodo_b->getItem()->getCodigo() << endl;
    qDebug() << "*********************************************" << endl;

    if (nodo_a->getItem()->comparar(value) == 0)
        return nodo_a->getItem();
    if (nodo_b->getItem()->comparar(value) == 0)
        return nodo_b->getItem();
    if (nodo_m->getItem()->comparar(value) == 0)
        return nodo_m->getItem();
    else
    {
        if (nodo_m->getItem()->comparar(value) > 0)
            return busquedaBinaria(0, m, nodo_a, nodo_m, value);
        else
        {
            b = b - m;
            return busquedaBinaria(0, b, nodo_m, nodo_b, value);
        }
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
    return primero == NULL;
}

bool ListaProducto::agregar(TADProducto *producto)
{
    if (vacio())
    {
        primero = ultimo = new NodoProducto(producto);;
        primero->setAnterior(ultimo);
        ultimo->setSiguiente(primero);

        return true;
    }

    if (primero->getItem()->comparar(producto) > 0)
        return agregarPrimero(producto);

    if (producto->comparar(ultimo->getItem()) > 0)
        return agregarUltimo(producto);

    NodoProducto *nuevo = new NodoProducto(producto);
    if (!agregar(primero->getSiguiente(), nuevo))
    {
        delete nuevo;
        nuevo = NULL;
        return false;
    }
    else
        return true;
}

bool ListaProducto::actualizar(QString _codigo, TADProducto *producto)
{
    if (producto->comparar(_codigo) != 0)
    {
        if (buscar(_codigo) != NULL)
            return false;

        if (contar() == 1)
        {
            producto->setCodigo(_codigo);
            return true;
        }

        NodoProducto *temp = buscar(producto->getCodigo());
        temp->getAnterior()->setSiguiente(temp->getSiguiente());
        temp->getSiguiente()->setAnterior(temp->getAnterior());

        if (temp == primero)
            primero = temp->getSiguiente();
        if (temp == ultimo)
            ultimo = temp->getAnterior();

        producto->setCodigo(_codigo);
        temp->setAnterior(NULL);
        temp->setSiguiente(NULL);

        if (primero->getItem()->comparar(producto) > 0)
        {
            ultimo->setSiguiente(temp);
            primero->setAnterior(temp);
            temp->setSiguiente(primero);
            temp->setAnterior(ultimo);
            primero = temp;

            return true;
        }

        if (producto->comparar(ultimo->getItem()) > 0)
        {
            ultimo->setSiguiente(temp);
            primero->setAnterior(temp);
            temp->setSiguiente(primero);
            temp->setAnterior(ultimo);
            ultimo = temp;

            return true;
        }

        return agregar(primero->getSiguiente(), temp);
    }
    else
        return true;
}

bool ListaProducto::agregarPrimero(TADProducto *producto)
{
    NodoProducto *nuevo = new NodoProducto(producto);

    if (!vacio())
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        primero->setAnterior(nuevo);

        primero = nuevo;
        return true;
    }

    primero = ultimo = nuevo;
    primero->setSiguiente(nuevo);
    primero->setAnterior(nuevo);

    return true;
}

bool ListaProducto::agregarUltimo(TADProducto *producto)
{
    NodoProducto *nuevo = new NodoProducto(producto);

    if (!vacio())
    {
        nuevo->setSiguiente(primero);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        primero->setAnterior(nuevo);

        ultimo = nuevo;
        return true;
    }

    primero = ultimo = nuevo;
    primero->setSiguiente(nuevo);
    primero->setAnterior(nuevo);

    return true;
}

int ListaProducto::contar()
{
    int i = 0;

    NodoProducto *temp = primero;

    while(temp != NULL)
    {
        i++;
        if (temp->getSiguiente() != primero)
            temp = temp->getSiguiente();
        else
            temp = NULL;
    }

    return i;
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

TADProducto *ListaProducto::obtener(QString value)
{
    NodoProducto *nodo = buscar(value);
    if (nodo != NULL)
        return nodo->getItem();
    else
        return NULL;
}

TADProducto *ListaProducto::busquedaBinaria(QString value)
{
    int a, b, m = 0;
    b = contar();
    m = (b - a) / 2;

    NodoProducto *nodo_a, *nodo_b, *nodo_m;
    nodo_a = primero;
    nodo_b = ultimo;
    nodo_m = primero;

    for (int i = 0; i < m; i++)
        nodo_m = nodo_m->getSiguiente();

    qDebug() << "*********************************************" << endl;
    qDebug() << "Encontrar: " << value;
    qDebug() << "---------------------------------------------";
    qDebug() << "Extremo a: " << nodo_a->getItem()->getCodigo();
    qDebug() << "Medio: " << nodo_m->getItem()->getCodigo();
    qDebug() << "Extremo b: " << nodo_b->getItem()->getCodigo();
    qDebug() << "*********************************************" << endl;

    if (nodo_a->getItem()->comparar(value) == 0)
        return nodo_a->getItem();
    if (nodo_b->getItem()->comparar(value) == 0)
        return nodo_b->getItem();
    if (nodo_m->getItem()->comparar(value) == 0)
        return nodo_m->getItem();
    else
    {
        if (nodo_m->getItem()->comparar(value) > 0)
            return busquedaBinaria(0, m, nodo_a, nodo_m, value);
        else
        {
            b = b - m;
            return busquedaBinaria(0, b, nodo_m, nodo_b, value);
        }
    }
}

bool ListaProducto::eliminar(QString value)
{
    if (contar() == 1)
    {
        delete primero;
        primero = ultimo = NULL;
        return true;
    }
    else
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
    system("eog listaProducto.png");

    std::cout << "Creación de grafo completado" << std::endl;
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
