ArbolEx::ArbolEx()
{
    this->raiz = NULL;
    this->ultAgregado = NULL;
}

ArbolEx::~ArbolEx()
{

}

void ArbolEx::fijarRaiz(NodoEx* nRaiz)
{
    this->raiz = nRaiz;
}

NodoEx* ArbolEx::darRaiz()
{
    return this->raiz;
}

void ArbolEx::fijarUltAgregado(NodoEx* nUltAgregado)
{
    this->ultAgregado = nUltAgregado;
}

NodoEx* ArbolEx::darUltAgregado()
{
    return this->ultAgregado;
}

void ArbolEx::agregarNodoPrefijo(std::string dato)
{
    NodoEx* n = new NodoEx();
    n->fijarDato(dato);

    if(this->raiz == NULL)
    {
        this->fijarRaiz(n);
    }
    else
    {
        if(this->ultAgregado->esNumero() == true)
        {
            NodoEx* padre = this->raiz->buscarPadre(this->ultAgregado);
            NodoEx* conHijos = NULL;

            while(conHijos == NULL)
            {
                if(padre->darIzquierdo() != NULL && padre->darDerecho() != NULL)
                {
                    padre = this->raiz->buscarPadre(padre);
                }
                else
                {
                    conHijos = padre;
                }
            }

            conHijos->fijarDerecho(n);
        }
        else
        {
            if(ultAgregado->darIzquierdo() != NULL)
            {
                if(ultAgregado->darDerecho() != NULL)
                {
                    NodoEx* padre = this->raiz->buscarPadre(ultAgregado);
                    NodoEx* conHijos = NULL;

                    while(conHijos == NULL)
                    {
                        if(padre->darIzquierdo() != NULL && padre->darDerecho() != NULL)
                        {
                            padre = this->raiz->buscarPadre(padre);
                        }
                        else
                        {
                            conHijos = padre;
                        }
                    }

                    conHijos->fijarDerecho(n);
                }
                else
                {
                    ultAgregado->fijarDerecho(n);
                }
            }
            else
            {
                ultAgregado->fijarIzquierdo(n);
            }
        }
    }

    this->fijarUltAgregado(n);
}

void ArbolEx::agregarNodoPosfijo(std::string dato)
{
    NodoEx* n = new NodoEx();
    n->fijarDato(dato);

    if(this->raiz == NULL)
    {
        this->fijarRaiz(n);
    }
    else
    {
        if(this->ultAgregado->esNumero() == true)
        {
            NodoEx* padre = this->raiz->buscarPadre(ultAgregado);
            NodoEx* conHijos = NULL;

            while(conHijos == NULL)
            {
                if(padre->darIzquierdo() != NULL && padre->darDerecho() != NULL)
                {
                    padre = this->raiz->buscarPadre(padre);
                }
                else
                {
                    conHijos = padre;
                }
            }

            conHijos->fijarIzquierdo(n);
        }
        else
        {
            if(ultAgregado->darDerecho() != NULL)
            {
                if(ultAgregado->darIzquierdo() != NULL)
                {
                    NodoEx* padre = this->raiz->buscarPadre(ultAgregado);
                    NodoEx* conHijos = NULL;

                    while(conHijos == NULL)
                    {
                        if(padre->darIzquierdo() != NULL && padre->darDerecho() != NULL)
                        {
                            padre = this->raiz->buscarPadre(padre);
                        }
                        else
                        {
                            conHijos = padre;
                        }
                    }

                    conHijos->fijarIzquierdo(n);
                }
                else
                {
                    ultAgregado->fijarIzquierdo(n);
                }
            }
            else
            {
                ultAgregado->fijarDerecho(n);
            }
        }
    }

    this->fijarUltAgregado(n);
}

void ArbolEx::generarExpresionPrefija()
{
    std::string resp = "El arbol esta vacio.";

    if(this->raiz == NULL)
    {
        std::cout << resp << std::endl;
    }
    else
    {
        resp = this->raiz->generarExpresionPrefija();
        std::cout << resp << std::endl;
    }
}

void ArbolEx::generarExpresionPosfija()
{
    std::string resp = "El arbol esta vacio.";

    if(this->raiz == NULL)
    {
        std::cout << resp << std::endl;
    }
    else
    {
        resp = this->raiz->generarExpresionPosfija();
        std::cout << resp << std::endl;
    }
}

void ArbolEx::generarExpresionInfija()
{
    std::string resp = "El arbol esta vacio.";

    if(this->raiz == NULL)
    {
        std::cout << resp << std::endl;
    }
    else
    {
        resp = this->raiz->generarExpresionInfija();
        std::cout << resp << std::endl;
    }
}

//void ArbolEx::evaluarExpresion()
//{
//    int resp = 0;
//
//    if(this->raiz == NULL)
//    {
//        std::cout << "El arbol esta vacio: " << resp << std::endl;
//    }
//    else
//    {
//        resp = this->raiz->evaluarExpresion();
//        std::cout << "El resultado de la expresion es: " << resp << std::endl;
//    }
//}
