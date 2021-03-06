/** ICP Project 2019/2020: Bus Tracker
 * @file mainwindow.h
 * @brief Trida, ktera ovlada hlavni okno programu, zapina jizdu, atd... (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class Vehicle;
class Street;
class QTimer;
class Line;
class Drawable;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow konstrukto tridy
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

    /**
     * @brief zoomIn priblizeni obrazu
     */
    void zoomIn();

    /**
     * @brief zoomOut oddaleni obrazu
     */
    void zoomOut();

    /**
     * @brief restart restartuje priblizeni (resp. oddaleni)
     */
    void restart();

    /**
     * @brief showVehicleRoute zobrazi trasu nakliknuteho vozidla a vypise informace o nem
     * @param vehicle vozidlo
     */
    void showVehicleRoute(Vehicle *vehicle);

    /**
     * @brief showStreet zobrazi informace o nakliknute ulici
     * @param street ulici
     */
    void showStreet(Street *street,bool firstTime);

    /**
     * @brief setCongestionDegree nastavi "ucpanost" ulice
     */
    void setCongestionDegree();

    /**
     * @brief stop pozastavi simulaci
     */
    void stop();

    /**
     * @brief getLines ziska seznam linek
     * @return
     */
    std::vector<Line *> getLines();

    /**
     * @brief showNewRoute zobrazi novou trasu pro danou linku
     * @param line
     */
    void showNewRoute(Line* line, std::vector<Street*>);

public slots:
    /**
     * @brief setTimer nastavi casovac
     */
    void setTimer();

    /**
     * @brief stopPlay ovlada tlacitko pro pozastaveni simulace
     */
    void stopPlay();

    /**
     * @brief updatemainTime aktualizace casu
     */
    void updatemainTime();

    /**
     * @brief resetTime restart casovace
     */
    void resetTime();

    /**
     * @brief setTime nastaveni casovace
     */
    void setTime();

    /**
     * @brief updateLines aktualizace stavu linek
     */
    void updateLines();

    /**
     * @brief setEditMode nastavi vzhled okna pro zobrazeni editace
     */
    void setEditMode();

    /**
     * @brief setNormalMode nastavi vzhled pro bezne zobrazeni
     */
    void setNormalMode();

private:
    /**
     * @brief ui uzivatelske rozhrani okna
     */
    Ui::MainWindow *ui;

    /**
     * @brief timer casovac
     */
    QTimer* timer;

    /**
     * @brief mainTime aktualni cas v simulaci
     */
    unsigned mainTime;

    /**
     * @brief drawable
     */
    Drawable* drawable;

    /**
     * @brief lines seznam linek
     */
    std::vector<Line*> lines;


};
#endif // MAINWINDOW_H
