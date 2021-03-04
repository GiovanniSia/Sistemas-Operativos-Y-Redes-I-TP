#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
	red=`tput setaf 1`;
	green=`tput setaf 2`;
	blue=`tput setaf 4`;
	bg_blue=`tput setab 4`;
	reset=`tput sgr0`;
	bold=`tput setaf bold`;

#------------------------------------------------------
# TODO: Completar con su path
#------------------------------------------------------
proyectoActual=$(pwd);

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
	
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver estado del proyecto";
    echo -e "\t\t\t b.  Guardar cambios";
    echo -e "\t\t\t c.  Actualizar repo";
    echo -e "\t\t\t f.  Abrir en terminal";        
    echo -e "\t\t\t g.  Abrir en carpeta"; 
    echo -e "\t\t\t h.  Crear 100 carpetas";    
    echo -e "\t\t\t i.  Borar las 100 carpetas";
 	echo -e "\t\t\t j.  Estados de un Proceso"; 
    echo -e "\t\t\t k.  El barbero dormilon";
 	echo -e "\t\t\t m.  La opera de Gioachino Rossini"; 
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
	echo $1;
	while true; do
		echo "desea ejecutar? (s/n)";
    		read respuesta;
    		case $respuesta in
        		[Nn]* ) break;;
       			[Ss]* ) eval $1
				break;;
        		* ) echo "Por favor tipear S/s ó N/n.";;
    		esac
	done
}

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion () {
    	imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
	echo "---------------------------"        
	echo "Somthing to commit?"
        decidir "cd $proyectoActual; git status";

        echo "---------------------------"        
	echo "Incoming changes (need a pull)?"
	decidir "cd $proyectoActual; git fetch origin"
	decidir "cd $proyectoActual; git log HEAD..origin/master --oneline"
}

b_funcion () {
       

	git config --global user.name "Giovanni Sia"
	git config --global user.email "giovanni_sia@yahoo.com"


	imprimir_encabezado "\tOpción b.  Guardar cambios";
      

 	git init
	git remote add origin https://gitlab.com/Giovanni_S/tp-1.git
	
	git push -u origin master
	
	decidir "cd $proyectoActual; git add -A";
   	echo "Ingrese mensaje para el commit:";
   	read mensaje;
   	decidir "cd $proyectoActual; git commit -m \"$mensaje\"";
	decidir "cd $proyectoActual; git push";
}

c_funcion () {
      	imprimir_encabezado "\tOpción c.  Actualizar repo";
      	decidir "cd $proyectoActual; git pull";   	 
}


f_funcion () {
	imprimir_encabezado "\tOpción f.  Abrir en terminal";        
	decidir "cd $proyectoActual; xterm &";
}

g_funcion () {
	imprimir_encabezado "\tOpción g.  Abrir en carpeta";        
	decidir "gnome-open $proyectoActual &";
}
#------------------------------------------------------
# TODO: Completar con el resto de ejercicios del TP, una funcion por cada item
#------------------------------------------------------
h_funcion () {
	imprimir_encabezado "\tOpción h.  Crear 100 carpetas";        
	for i in {0..99}
		do

			#Creo las carpetas
			mkdir grupo$i
			chmod 640 grupo$i
			
   
		done
}
i_funcion () {
	imprimir_encabezado "\tOpción i.  Borrar las 100 carpetas";        
	for i in {0..99}	
		do		
			cd $proyectoActual
			
			rmdir grupo$i
			
		done	
}
j_funcion(){
	imprimir_encabezado "\tOpción j. Estados de un Proceso";

	./Estados_De_Un_Proceso;

}
k_funcion(){
    imprimir_encabezado "\tOpción k. El barbero dormilon";
    ./El_Barbero_Dormilon
}    
m_funcion(){
	imprimir_encabezado "\tOpción m. La opera de Gioachino Rossini";

	./figaro;
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
        h|H) h_funcion;;
        i|I) i_funcion;;
		j|J) j_funcion;;
		k|K) k_funcion;;
        m|M) m_funcion;;
	q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done
 