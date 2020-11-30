#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QAbstractButton>
#include <QBrush>
#include <QPropertyAnimation>

class SwitchButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
public:
    SwitchButton(QColor thumbColor, QColor trackColor, QWidget *parent = nullptr);

    QSize sizeHint() const override;

    int offset();

    void setOffset(int o);

    void setChecked(bool checked);

    void toggle();

signals:

protected:

    void paintEvent(QPaintEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void enterEvent(QEvent *e) override;

private:
    int32_t x;
    int32_t y;
    int32_t _height;
    int32_t margin = 2;

    QColor thumbColor;
    QColor trackColor;
    QColor offColor = "#D5D5D5";
    QColor disabledColor = "#BDBDBD";

    QBrush thumb;
    QBrush track;

    QPropertyAnimation *animation = nullptr;
};

#endif // SWITCHBUTTON_H
