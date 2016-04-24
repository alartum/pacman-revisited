// ************************************************************
//*                    GameMenu                                *
//* Окно, предоставляющее пользователю возможность начать игру.*
//* Является стартовым окном приложения-игры.                  *
// ************************************************************
#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class GameMenu;
}

class GameMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();

private slots:
    // Вспомогательный слот.
    void on_startButton_clicked();
signals:
    // Нажали на кнопку "Новая игра".
    void startClicked();
private:
    Ui::GameMenu *ui;
};

#endif // GAMEMENU_H
