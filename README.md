## TP Criptografia y Seguridad

####Es necesario tener instalado CMAKE para poder compilar correctamente el proyecto.
Se puede instalar siguiendo los simples pasos que se encuentran en https://cgold.readthedocs.io/en/latest/first-step/installation.html


####Una vez que contemos con CMAKE instalado y sobre el directorio del trabajo practico ejecutamos:
1) cmake CMakeLists.txt
2) make

###Para distribuir una imagen secreta en otras imágenes:

> ./TP_Cripto d imagenSecreta k directorio

Ejemplo:
> ./TP_Cripto d imageToHide.bmp 4 images/

Significado de los argumentos:
- imagenSecreta: Archivo de extension .bmp, este archivo debe existir, es la imagen a ocultar y debe ser en blanco y negro.
- k: La cantidad mínima de sombras necesarias para
  recuperar el secreto en un esquema (k, n)
- directorio: El directorio donde están las imágenes que
  contienen oculto el secreto. Debe contener
  imágenes de extensión .bmp, de 8 bits por pixel, de igual tamaño que la imagen secreta.
  Además, deberá verificarse que existan por lo menos k imágenes en el directorio.

###Para recuperar una imagen secreta a partir de otras imágenes:

> ./TP_Cripto r imagenSecreta k directorio

Ejemplo:
> ./TP_Cripto r imageRevealed.bmp 4 images/

Significado de los argumentos:
- imagenSecreta: Archivo de extension .bmp, será el archivo de salida, con la imagen secreta revelada al finalizar el programa.
- k: La cantidad mínima de sombras necesarias para
  recuperar el secreto en un esquema (k, n)
- directorio: El directorio donde se encuentran las imágenes en las que se distribuirá el
  secreto. Debe contener
  imágenes de extensión .bmp, de 8 bits por pixel, de igual tamaño que la imagen secreta.
  Además, deberá verificarse que existan por lo menos k imágenes en el directorio.
  