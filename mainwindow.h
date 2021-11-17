/* #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    enum class SideMenuButton {
        CLINIC = 1, HOSPITAL = 2, SILVER_MINE = 3, GOLD_MINE = 4, HOUSE = 5, APARTMENT = 6, DEMOLISH = 7, NAVIGATE = 8
    };

    enum class OverlayButton {
        NORMAL, TYPE, NEIGHBOR
    };

    enum class SideMenuStatus {
        HIDDEN, HIDDEN_TO_VISIBLE, VISIBLE, VISIBLE_TO_HIDDEN
    };

    MainWindow(City *const city, QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

    SideMenuButton get_selected_side_menu_button();
    OverlayButton get_selected_overlay_button();
    SideMenuStatus get_side_menu_status();
    void set_side_menu_status(SideMenuStatus status);

private:
    // Initialization functions, called in constructor
    void initialize_overlay_buttons();
    void initialize_side_menu_buttons();

    void on_overlay_button_clicked(OverlayButton button);
    void on_side_menu_button_clicked(SideMenuButton button);

    void main_loop();

    Ui::MainWindow* ui;

    City *const city;

    QTimer* loop_timer;

    SideMenuButton selected_side_menu_button;
    OverlayButton selected_overlay_button;
    SideMenuStatus side_menu_status;

    friend class GameWidget;
};
#endif // MAINWINDOW_H
*/
