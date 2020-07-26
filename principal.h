#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionLineas_triggered();

    void on_actionLibre_triggered();

    void on_actionRect_ngulo_triggered();

    void on_actionCircunferencias_triggered();

private:
    Ui::Principal *ui;
    QImage *mImagen;    //Imagen sobre la que se va a dibujar
    QPainter *mPainter; // Painter de la Imagen
    QPoint mInicial;    //Punto inicial para dibujar la linea
    QPoint mFinal;      //Punto final para dibujar la linea
    bool mPuedeDibujar; //Determina si debe o no dibujar
    int mAncho;         //Define el ancho del pincel
    QColor mColor;      //Define el color del pincel
    int mNumLineas;

    int mSeleccion;         // Esta variable define en que modo voy a dibujar

};
#endif // PRINCIPAL_H
