/* Autor: Joselyn Chérrez
 * PROGRAMACION ORIENTADA A OBJETOS
 *
 * PROGRAMA MIPAINT
 *
 */

#include "principal.h"
#include "ui_principal.h"

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;

    mSeleccion = 2;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    //Variable local
    //Crear el painter de la ventana principal)
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0,0, *mImagen);
    //Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Invocar a Seleccion para que dibuje libremente
    if(mSeleccion==2){
        mPuedeDibujar = false;
        //Capturar el punto donde se suelta el mouse
        mFinal = event->pos();
        //Establecer un pincel
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        //Dibujar libremente
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial,mFinal);
        //Contar las lineas
        ui->statusbar->showMessage("Número de lineas: "+QString::number(++mNumLineas));
        update();
        mInicial=mFinal;
    }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{

      if(mSeleccion==1){
          mPuedeDibujar = false;
          // Capturar el punto donde se suelta el mouse
          mFinal = event->pos();
          //Establecer un pincel
          QPen pincel;
          pincel.setColor(mColor);
          pincel.setWidth(mAncho);
          //Dibujar una linea
          mPainter->setPen(pincel);
          mPainter->drawLine(mInicial,mFinal);
          //Contar las lineas
          ui->statusbar->showMessage("Número de lineas: "+QString::number(++mNumLineas));
          //Actualizar
          update();
          // Aceptar el evento
          event->accept();
      }

      if(mSeleccion==3){
          mPuedeDibujar = false;
          // Capturar el punto donde se suelta el mouse
          mFinal = event->pos();
          //Establecer un pincel
          QPen pincel;
          pincel.setColor(mColor);
          pincel.setWidth(mAncho);
          QRect rectangulo(mInicial,mFinal);
          // Dibujar un Rectangulo
          mPainter->setPen(pincel);
          mPainter->drawRect(rectangulo);
          //Contar lineas
          ui->statusbar->showMessage("Número de lineas: "+QString::number(++mNumLineas));
          //Actualizar
          update();
          // Aceptar el vento
          event->accept();
      }
      //  Seleccion 4 para dibujar circulos
      if(mSeleccion==4){
          mPuedeDibujar = false;
          // Capturar el punto donde se suelta el mouse
          mFinal = event->pos();
          QPen pincel;
          pincel.setColor(mColor);
          pincel.setWidth(mAncho);
          //Establecer una variable circuferencia con los puntos
          QRectF circunferencia(mInicial,mFinal);
          // Dibujar una circunferencia
          mPainter->setPen(pincel);
          mPainter->drawEllipse(circunferencia);
          //Contar las lineas
          ui->statusbar->showMessage("Número de lineas: "+QString::number(++mNumLineas));
          update();
          // Aceptar el evento
          event->accept();
      }
}



void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,"Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo", mAncho
                                  ,1,100);
}

void Principal::on_actionSalir_triggered()
{
    QString nombreArchivo;
    if(!mImagen->save(nombreArchivo)){
        QMessageBox msgBox;
        msgBox.setText("No se ha guardado la imagen.");
        msgBox.addButton("Guardar", QMessageBox::AcceptRole);
        msgBox.addButton("Cancelar", QMessageBox::RejectRole);
        msgBox.addButton("Salir sin guardar", QMessageBox::DestructiveRole);
        int guardar = msgBox.exec();
        switch (guardar) {
        case QMessageBox::AcceptRole:
            on_actionGuardar_triggered();
            break;
        case QMessageBox::RejectRole:
            break;
        case QMessageBox::DestructiveRole:
          mImagen->fill(Qt::white);
            break;
        default:
            break;
        }

    }

}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,this,"Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    QString nombreArchivo;
    if(!mImagen->save(nombreArchivo)){
        QMessageBox msgBox;
        msgBox.setText("No se ha guardado la imagen.");
        msgBox.addButton("Guardar", QMessageBox::AcceptRole);
        msgBox.addButton("Cancelar", QMessageBox::RejectRole);
        msgBox.addButton("Continuar", QMessageBox::DestructiveRole);
        int guardar = msgBox.exec();
        switch (guardar) {
        case QMessageBox::AcceptRole:
            on_actionGuardar_triggered();
            break;
        case QMessageBox::RejectRole:
            break;
        case QMessageBox::DestructiveRole:
          mImagen->fill(Qt::white);
            break;
        default:
            break;
        }

    }

    mNumLineas = 0;
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                             "Guardar imagen",
                                                             QString(),
                                                             "Imágenes (*.png)");
        if ( !nombreArchivo.isEmpty() ){
            if (mImagen->save(nombreArchivo))
                QMessageBox::information(this,
                                         "Guardar imagen",
                                         "Archivo almacenado en: " + nombreArchivo);
            else
                QMessageBox::warning(this,
                                     "Guardar imagen",
                                     "No se pudo almacenar la imagen.");
        }
}

void Principal::on_actionLineas_triggered()
{
    ui->actionLibre->setCheckable(false);
    ui->actionRect_ngulo->setChecked(false);
    ui->actionCircunferencias->setCheckable(false);

    mSeleccion=1;
}

void Principal::on_actionLibre_triggered()
{
    ui->actionLineas->setCheckable(false);
    ui->actionRect_ngulo->setChecked(false);
    ui->actionCircunferencias->setCheckable(false);

    mSeleccion=2;
}

void Principal::on_actionRect_ngulo_triggered()
{
    ui->actionLibre->setCheckable(false);
    ui->actionLineas->setCheckable(false);
    ui->actionCircunferencias->setCheckable(false);
    mSeleccion=3;
}

void Principal::on_actionCircunferencias_triggered()
{
    ui->actionLibre->setCheckable(false);
    ui->actionLineas->setCheckable(false);
    ui->actionLineas->setCheckable(false);

   mSeleccion=4;
}
