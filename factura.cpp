#include<iostream>
#include<string.h>
#include<locale.h>
#include<windows.h>
using namespace std;

void gotoxy(int x,int y){
    HANDLE hcon;
    hcon=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon,dwPos);
}

struct Cliente{
    string cedula;
    string nombres;
    string direccion;
    string telefono;
    string correo;
    bool estado;
    Cliente *sigt;
    Cliente *ant;
};

struct Producto{
    string cod_prod;
    string nombre;
    float precioU;
    bool aplicaiva;
    bool estado;
    Producto *sigt;
    Producto *ant;
};

struct DetallaFac{
    string cod_prod;
    string nombre_prod;
    float candidad;
    float pvp;
    bool aplicaIva;
    float total;
    float iva;
    DetallaFac *sigt;
    DetallaFac *ant;    
};

struct Factura{
    string numFac;
    string fechaFac;
    Cliente *dirCliente;
    DetallaFac *pcabDetFac;
    DetallaFac *pfinDetfac;
    float base15;
    float base0;
    float ivaFac;
    float TotalFac;
    bool estado;
    Factura *sigt;
    Factura *ant;
};

int menu();
void operaciones(int op,Producto *&pacbProd,Producto *&pfinProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac,Factura *&pfinFac);
int menuProductos();
void operacionesProducto(int op2, Producto *&pacbProd,Producto *&pfinProd);
Producto *fun_Buscar(Producto *pcab,string datoBuscar);
void fun_registrarProducto(Producto *&pacbProd,Producto *&pfinProd);
void fun_listarProducto(Producto *pcab);
void fun_modificarProducto(Producto *pcab);
void fun_darBajaProducto(Producto *pcab);

int menuClientes();
void operacionesCliente(int op2, Cliente *&pcabCli, Cliente *&pfinCli);
void fun_registrarCliente(Cliente *&pcab, Cliente *&pfin);
Cliente *buscarCliente(Cliente *pcab, string cedula);
void fun_listarClientes(Cliente *pcab);
void fun_modificarCliente(Cliente *pcab);
void fun_eliminarCliente(Cliente *&pcab, Cliente *&pfin);

int menuFactura();
void operacionesFactura(int op,Producto *pacbProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac, Factura*&pfinFac);
Factura *fun_buscarFactura(string datoBuscar,Factura *pcab);
void fun_registrarFactura(Producto *pacbProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac, Factura*&pfinFac);
void fun_recuperarCliente(Cliente *dirCliente);
void fun_registrarVentas(DetallaFac *&pcabDetFac,DetallaFac *&pfinDetfac,Producto *pacbProd,float &subtotal15,float &subtotal0,float &totalIva,float &tatalFactura);
void fun_mostrarFactura(Factura *fac);
void fun_anularFactura(Factura *&pcabFac);

int main(){
    setlocale(LC_CTYPE, "Spanish");
    Factura *pcabFac=NULL;
    Factura *pfinFac=NULL;
    Producto *pacbProd=NULL;
    Producto *pfinProd=NULL;
    Cliente *pcabCli=NULL;
    Cliente *pfinCli=NULL;
    int op;
    do{
        system("cls");
        op=menu();
        operaciones(op,pacbProd,pfinProd,pcabCli,pfinCli,pcabFac,pfinFac);
        cout<<" \n Desea realizar otra operación SI(1)";
        cin>>op;
    }while(op==1);
    system("pause");
    return 0;
}

int menu(){
    int op;
    do{
        cout<<"***OPERACIONES****"<<endl;
        cout<<"1: Productos "<<endl;
        cout<<"2: Clientes "<<endl;
        cout<<"3: Facturas "<<endl;
        cout<<"Elija la operación: ";
        cin>>op;
    }while(op<1 ||op>3);
    return op;
}

int menuProductos(){
    int op;
    do{
        cout<<"***OPERACIONES PRODUCTO****"<<endl;
        cout<<"1: Registrar "<<endl;
        cout<<"2: Listar Productos "<<endl;
        cout<<"3: Modificar un Producto "<<endl;
        cout<<"4: Dar de baja un Producto "<<endl;
        cout<<"Elija la operación: ";
        cin>>op;
    }while(op<1 ||op>4);
    return op;
}

int menuClientes(){
    int op;
    do{
        cout<<"*** OPERACIONES CLIENTES ***"<<endl;
        cout<<"1: Registrar cliente"<<endl;
        cout<<"2: Listar clientes"<<endl;
        cout<<"3: Modificar cliente"<<endl;
        cout<<"4: Eliminar cliente"<<endl;
        cout<<"Elija la operación: ";
        cin>>op;
    }while(op < 1 || op > 4);
    return op;
}

int menuFactura(){
    int op;
    do{
        system("cls");
        cout<<"***OPERACIONES FACTURA****"<<endl;
        cout<<"1: FACTURAR "<<endl;
        cout<<"2: Buscar FACTURA "<<endl;
        cout<<"3: Anular la Factura "<<endl;
        cout<<"Elija la operación: ";
        cin>>op;
    }while(op<1 ||op>3);
    return op;    
}

void operaciones(int op,Producto *&pacbProd,Producto *&pfinProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac,Factura *&pfinFac){
    int op2;
    switch(op){
        case 1:
            do{
                op2=menuProductos();
                operacionesProducto(op2,pacbProd,pfinProd);
                cout<<" \n Desea realizar otra operación con Productos SI(1)";
                cin>>op2;
            }while(op2==1);
            break;
        case 2:
            do {
                op2 = menuClientes();
                operacionesCliente(op2, pcabCli, pfinCli);
                cout << " ¿Desea realizar otra operación con Clientes? SI(1): ";
                cin >> op2;
            } while(op2 == 1);
            break;
        case 3:
            do{
                op2=menuFactura();
                operacionesFactura(op2,pacbProd,pcabCli,pfinCli,pcabFac,pfinFac);
                cout<<"\n Desea registrar otra Factura SI(1)";
                cin>>op2;
            }while(op2==1);
            break;
    }
}

void operacionesFactura(int op,Producto *pacbProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac, Factura*&pfinFac){
    switch(op){
        case 1:
            fun_registrarFactura(pacbProd,pcabCli,pfinCli,pcabFac,pfinFac);
            break;
        case 2:
            {
                string numFac;
                cout << "Ingrese el número de factura a buscar: ";
                cin >> numFac;
                Factura *fac = fun_buscarFactura(numFac, pcabFac);
                fun_mostrarFactura(fac);
                break;
            }
        case 3:
            fun_anularFactura(pcabFac);
            break;
    }
}

void fun_registrarFactura(Producto *pacbProd,Cliente *&pcabCli,Cliente *&pfinCli,Factura *&pcabFac, Factura*&pfinFac){
    string fecha,numFac,cedula;
    float subtotal15=0;
    float subtotal0=0;
    float totalIva=0;
    float tatalFactura=0;

    Factura *dirFactura;
    Cliente *dirCliente;
    cout<<"Fecha: ";
    cin>>fecha;
    cout<<"#FACTURA:";
    cin>>numFac;
    
    dirFactura=fun_buscarFactura(numFac,pcabFac);
    if(dirFactura!=NULL){
        cout<<"Este número de factura ya se encuentra registrado. ";
    }else{
        cout<<"CI/RUC:";
        cin>>cedula;
        dirCliente=buscarCliente(pcabCli,cedula);
        if(dirCliente!=NULL){
            fun_recuperarCliente(dirCliente);
        }else{
            Cliente *nuevoCliente;
            nuevoCliente=new(Cliente);
            nuevoCliente->cedula=cedula;
            cin.ignore();
            cout<<"NOMBRES: ";getline(cin,nuevoCliente->nombres);
            cout<<"DIRECCIÓN: ";getline(cin,nuevoCliente->direccion);
            cout<<"TELÉFONO: ";cin>>nuevoCliente->telefono;
            cout<<"CORREO: ";cin>>nuevoCliente->correo;
            nuevoCliente->estado = true;
            nuevoCliente->sigt=NULL;
            nuevoCliente->ant=NULL;
            if(pcabCli==NULL){
                pcabCli=nuevoCliente;
            }else{
                pfinCli->sigt=nuevoCliente;
                nuevoCliente->ant=pfinCli;
            }
            pfinCli=nuevoCliente;
            dirCliente=nuevoCliente;
        }
        
        Factura *nuevaFactura;
        nuevaFactura=new(Factura);
        nuevaFactura->numFac=numFac;
        nuevaFactura->fechaFac=fecha; 
        nuevaFactura->dirCliente=dirCliente;
        nuevaFactura->pcabDetFac=NULL;
        nuevaFactura->pfinDetfac=NULL;

        fun_registrarVentas(nuevaFactura->pcabDetFac,nuevaFactura->pfinDetfac,pacbProd,subtotal15,subtotal0,totalIva,tatalFactura);

        nuevaFactura->base15=subtotal15;
        nuevaFactura->base0=subtotal0;
        nuevaFactura->ivaFac=totalIva;
        nuevaFactura->TotalFac=tatalFactura;
        nuevaFactura->estado=true;

        nuevaFactura->sigt=NULL;
        nuevaFactura->ant=NULL;
        if(pcabFac==NULL){
            pcabFac=nuevaFactura;
        }else{
            pfinFac->sigt=nuevaFactura;
            nuevaFactura->ant=pfinFac;
        }
        pfinFac=nuevaFactura;
        
        cout<<"Factura registrada exitosamente!"<<endl;
        cout<<"Total factura: "<<nuevaFactura->TotalFac<<endl;
    }
}

Factura *fun_buscarFactura(string datoBuscar,Factura *pcab){
    Factura *nodoActual=pcab;
    while(nodoActual!=NULL){
        if(nodoActual->numFac==datoBuscar){
            return nodoActual;
        }        
        nodoActual=nodoActual->sigt;    
    }
    return NULL;    
}

void fun_recuperarCliente(Cliente *dirCliente){
    cout<<"NOMBRES: "<<dirCliente->nombres<<endl;
    cout<<"DIRECCIÓN: "<<dirCliente->direccion<<endl;
    cout<<"TELÉFONO: "<<dirCliente->telefono<<endl;
    cout<<"CORREO: "<<dirCliente->correo<<endl;
}

void fun_registrarVentas(DetallaFac *&pcabDetFac,DetallaFac *&pfinDetfac,Producto *pacbProd,float &subtotal15,float &subtotal0,float &totalIva,float &tatalFactura){
    string cod_prod;
    int posY=15;
    int resp;
    Producto *dirProducto;
    system("cls");
    gotoxy(2,15);cout<<"CODIGO";
    gotoxy(20,15);cout<<"DESCRIPCION";
    gotoxy(40,15);cout<<"CANTIDAD";
    gotoxy(55,15);cout<<"PVP";
    gotoxy(65,15);cout<<"TOTAL";
    
    do{
        posY=posY+1;
        do{
            gotoxy(2,posY);cin>>cod_prod;
            dirProducto=fun_Buscar(pacbProd,cod_prod);
            if(dirProducto != NULL && !dirProducto->estado){
                cout<<"Producto inactivo. Seleccione otro.";
                dirProducto = NULL;
            }
        }while(dirProducto==NULL);
        
        gotoxy(20,posY);cout<<dirProducto->nombre;
        gotoxy(55,posY);cout<<dirProducto->precioU;
        float cantidad;
        gotoxy(40,posY);cin>>cantidad;
        float total=cantidad*dirProducto->precioU;
        gotoxy(65,posY);cout<<total;
        float iva;
        if(dirProducto->aplicaiva==1){
            iva=total*0.15;
            subtotal15=subtotal15+total;
        }else{
            iva=0;
            subtotal0=subtotal0+total;
        }
        totalIva=totalIva+iva;
        tatalFactura=subtotal15+subtotal0+totalIva;
        
        DetallaFac *nuevoDetalle=new (DetallaFac);
        nuevoDetalle->cod_prod=dirProducto->cod_prod;
        nuevoDetalle->nombre_prod=dirProducto->nombre;
        nuevoDetalle->candidad=cantidad;
        nuevoDetalle->pvp=dirProducto->precioU;
        nuevoDetalle->aplicaIva=dirProducto->aplicaiva;
        nuevoDetalle->total=total;
        nuevoDetalle->iva=iva;
        nuevoDetalle->sigt=NULL;
        nuevoDetalle->ant=NULL;
        if(pcabDetFac==NULL){
            pcabDetFac=nuevoDetalle;
        }else{
            pfinDetfac->sigt=nuevoDetalle;
            nuevoDetalle->ant=pfinDetfac;
        }
        pfinDetfac=nuevoDetalle;
        
        gotoxy(51,26);cout<<"SUB TOTAL"; gotoxy(65,26);cout<<subtotal15;
        gotoxy(51,27);cout<<"SUB TOTAL(0)"; gotoxy(65,27);cout<<subtotal0;
        gotoxy(51,28);cout<<"IVA"; gotoxy(65,28);cout<<totalIva;
        gotoxy(51,29);cout<<"TOTAL"; gotoxy(65,29);cout<<tatalFactura;
        
        gotoxy(30,33);cout<<"Si desea añadir otro producto SI(1)";
        cin>>resp;
    }while(resp==1);
}

void fun_mostrarFactura(Factura *fac){
    if(fac == NULL){
        cout<<"Factura no encontrada."<<endl;
        return;
    }
    system("cls");
    cout<<"======================================"<<endl;
    cout<<"          FACTURA #"<<fac->numFac<<endl;
    cout<<"Fecha: "<<fac->fechaFac<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"CLIENTE: "<<fac->dirCliente->nombres<<endl;
    cout<<"CI/RUC: "<<fac->dirCliente->cedula<<endl;
    cout<<"Dirección: "<<fac->dirCliente->direccion<<endl;
    cout<<"======================================"<<endl;
    cout<<"DETALLE DE LA FACTURA:"<<endl;
    cout<<"--------------------------------------"<<endl;
    
    DetallaFac *det = fac->pcabDetFac;
    while(det != NULL){
        cout<<det->cod_prod<<" - "<<det->nombre_prod;
        cout<<"  "<<det->candidad<<" x "<<det->pvp;
        cout<<" = "<<det->total;
        if(det->aplicaIva) cout<<" (IVA: "<<det->iva<<")";
        cout<<endl;
        det = det->sigt;
    }
    
    cout<<"--------------------------------------"<<endl;
    cout<<"SUBTOTAL 15%: "<<fac->base15<<endl;
    cout<<"SUBTOTAL 0%: "<<fac->base0<<endl;
    cout<<"IVA: "<<fac->ivaFac<<endl;
    cout<<"TOTAL FACTURA: "<<fac->TotalFac<<endl;
    cout<<"======================================"<<endl;
    cout<<"ESTADO: "<<(fac->estado ? "ACTIVA" : "ANULADA")<<endl;
}

void fun_anularFactura(Factura *&pcabFac){
    string numFac;
    cout<<"Ingrese el número de factura a anular: ";
    cin>>numFac;
    Factura *fac = fun_buscarFactura(numFac, pcabFac);
    if(fac == NULL){
        cout<<"Factura no encontrada."<<endl;
        return;
    }
    fac->estado = false;
    cout<<"Factura anulada correctamente."<<endl;
}

void operacionesProducto(int op2, Producto *&pacbProd,Producto *&pfinProd){
    switch(op2){
        case 1:
            fun_registrarProducto(pacbProd,pfinProd);
            break;
        case 2:
            fun_listarProducto(pacbProd);
            break;
        case 3:
            fun_modificarProducto(pacbProd);
            break;
        case 4:
            fun_darBajaProducto(pacbProd);
            break;
    }
}

void fun_registrarProducto(Producto *&pcab,Producto *&pfin){
    string codigo;
    Producto *dirProd;
    Producto *nuevoNodo;
    nuevoNodo=new(Producto);
    do{
        cout<<" Ingrese el código del producto: ";
        cin>>codigo;
        dirProd=fun_Buscar(pcab,codigo);    
    }while(dirProd!=NULL);
    nuevoNodo->cod_prod=codigo;
    cout<<"Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nuevoNodo->nombre);
    cout<<"Ingrese el precio unitario: ";
    cin>>nuevoNodo->precioU;
    cout<<"Aplica iva SI(1) NO(0): ";
    cin>>nuevoNodo->aplicaiva;
    nuevoNodo->estado=true;

    nuevoNodo->sigt=NULL;
    nuevoNodo->ant=NULL;
    if(pcab==NULL){
        pcab=nuevoNodo;    
    }else{
        pfin->sigt=nuevoNodo;
        nuevoNodo->ant=pfin;    
    }
    pfin=nuevoNodo;
    cout<<"Producto registrado exitosamente!"<<endl;
}

Producto *fun_Buscar(Producto *pcab,string datoBuscar){
    Producto *nodoActual=pcab;
    while(nodoActual!=NULL){
        if(nodoActual->cod_prod==datoBuscar){
            return nodoActual;
        }        
        nodoActual=nodoActual->sigt;    
    }
    return NULL;    
}

void fun_listarProducto(Producto *pcab){
    Producto *nodoAct=pcab;
    while(nodoAct!=NULL){
        cout<<"CODIGO: "<<nodoAct->cod_prod<<endl;
        cout<<"NOMBRE: "<<nodoAct->nombre<<endl;
        cout<<"PRECIO: "<<nodoAct->precioU<<endl;
        cout<<"APLICA IVA: "<<(nodoAct->aplicaiva ? "SI" : "NO")<<endl;
        cout<<"ESTADO: "<<(nodoAct->estado ? "ACTIVO" : "INACTIVO")<<endl;
        cout<<"-----------------------------------"<<endl;
        nodoAct=nodoAct->sigt;
    }
}

void fun_modificarProducto(Producto *pcab) {
    string codigo;
    cout << "Ingrese el código del producto a modificar: ";
    cin >> codigo;
    Producto *prod = fun_Buscar(pcab, codigo);
    if (prod == NULL) {
        cout << "Producto no encontrado." << endl;
        return;
    }
    cout << "Nuevo nombre (" << prod->nombre << "): ";
    cin.ignore();
    getline(cin, prod->nombre);
    cout << "Nuevo precio unitario (" << prod->precioU << "): ";
    cin >> prod->precioU;
    cout << "¿Aplica IVA? (1: Sí, 0: No) [" << prod->aplicaiva << "]: ";
    cin >> prod->aplicaiva;
    cout << "Producto modificado correctamente." << endl;
}

void fun_darBajaProducto(Producto *pcab) {
    string codigo;
    cout << "Ingrese el código del producto a dar de baja: ";
    cin >> codigo;
    Producto *prod = fun_Buscar(pcab, codigo);
    if (prod == NULL) {
        cout << "Producto no encontrado." << endl;
        return;
    }
    prod->estado = false;
    cout << "Producto dado de baja correctamente." << endl;
}

void operacionesCliente(int op2, Cliente *&pcabCli, Cliente *&pfinCli){
    switch(op2){
        case 1:
            fun_registrarCliente(pcabCli, pfinCli);
            break;
        case 2:
            fun_listarClientes(pcabCli);
            break;
        case 3:
            fun_modificarCliente(pcabCli);
            break;
        case 4:
            fun_eliminarCliente(pcabCli, pfinCli);
            break;
    }
}

void fun_registrarCliente(Cliente *&pcab, Cliente *&pfin){
    Cliente *nuevo = new Cliente;
    cout<<"Ingrese la cédula: ";
    cin>>nuevo->cedula;
    cout<<"Ingrese los nombres: ";
    cin.ignore();
    getline(cin, nuevo->nombres);
    cout<<"Ingrese la dirección: ";
    getline(cin, nuevo->direccion);
    cout<<"Ingrese el teléfono: ";
    cin>>nuevo->telefono;
    cout<<"Ingrese el correo: ";
    cin>>nuevo->correo;
    nuevo->estado = true;

    nuevo->sigt = NULL;
    nuevo->ant = NULL;

    if(pcab == NULL){
        pcab = pfin = nuevo;
    }else{
        pfin->sigt = nuevo;
        nuevo->ant = pfin;
        pfin = nuevo;
    }
    cout<<"Cliente registrado exitosamente!"<<endl;
}

void fun_listarClientes(Cliente *pcab){
    Cliente *actual = pcab;
    while (actual != NULL) {
        cout<<"Cédula: "<<actual->cedula<<endl;
        cout<<"Nombres: "<<actual->nombres<<endl;
        cout<<"Dirección: "<<actual->direccion<<endl;
        cout<<"Teléfono: "<<actual->telefono<<endl;
        cout<<"Correo: "<<actual->correo<<endl;
        cout<<"Estado: "<<(actual->estado ? "ACTIVO" : "INACTIVO")<<endl<<endl;
        actual = actual->sigt;
    }
}

Cliente *buscarCliente(Cliente *pcab, string cedula){
    Cliente *actual = pcab;
    while(actual != NULL){
        if(actual->cedula == cedula)
            return actual;
        actual = actual->sigt;
    }
    return NULL;
}

void fun_modificarCliente(Cliente *pcab){
    string cedula;
    cout<<"Ingrese la cédula del cliente a modificar: ";
    cin>>cedula;

    Cliente *cli = buscarCliente(pcab, cedula);
    if(cli == NULL){
        cout<<"Cliente no encontrado."<<endl;
        return;
    }

    cout<<"Cliente encontrado. Ingrese nuevos datos."<<endl;
    cout<<"Nombres actuales: "<<cli->nombres<<endl;
    cout<<"Nuevos nombres: ";
    cin.ignore();
    getline(cin, cli->nombres);

    cout<<"Nueva dirección: ";
    getline(cin, cli->direccion);

    cout<<"Nuevo teléfono: ";
    cin>>cli->telefono;

    cout<<"Nuevo correo: ";
    cin>>cli->correo;

    cout<<"Cliente modificado correctamente."<<endl;
}

void fun_eliminarCliente(Cliente *&pcab, Cliente *&pfin){
    string cedula;
    cout<<"Ingrese la cédula del cliente a eliminar: ";
    cin>>cedula;

    Cliente *cli = buscarCliente(pcab, cedula);
    if(cli == NULL){
        cout<<"Cliente no encontrado."<<endl;
        return;
    }

    if(cli == pcab && cli == pfin){
        pcab = pfin = NULL;
    }else if (cli == pcab){
        pcab = cli->sigt;
        pcab->ant = NULL;
    }else if (cli == pfin){
        pfin = cli->ant;
        pfin->sigt = NULL;
    }else {
        cli->ant->sigt = cli->sigt;
        cli->sigt->ant = cli->ant;
    }
    delete cli;

    cout<<"Cliente eliminado correctamente."<<endl;
}
