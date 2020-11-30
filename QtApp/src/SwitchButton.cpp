#include "SwitchButton.h"
#include <QMouseEvent>
#include <QPainter>
#include <iostream>

SwitchButton::SwitchButton(QColor thumbColor, QColor trackColor, QWidget *parent) :
    QAbstractButton(parent),
    _height(16),
    thumbColor(thumbColor),
    trackColor(trackColor),
    thumb(QBrush(offColor)),
    track(trackColor),
    animation(new QPropertyAnimation(this, "offset", this))
{
    setOffset(_height / 2);
    y = offset();
    animation->setDuration(100);

    QAbstractButton::setCheckable(true);
}

void SwitchButton::paintEvent(QPaintEvent *e) {
    (void) e;
    QPainter p(this);
    p.setPen(Qt::NoPen);

    if (isEnabled()) {
        p.setOpacity(0.5);
        p.setRenderHint(QPainter::Antialiasing, true);
    }
    else{
        p.setOpacity(0.12);
    }
    p.setBrush((isEnabled() && isChecked()) ? track : Qt::black);
    p.drawRoundedRect(QRect(margin, margin, width() - 2 * margin, height() - 2 * margin),
                      _height / 2, _height / 2);
    p.setOpacity(1.0);
    p.setBrush(isEnabled() ? thumb : disabledColor);
    p.drawEllipse(QRectF(offset() - (_height / 2), y - (_height / 2), height(), height()));
}

void SwitchButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() & Qt::LeftButton) {
        toggle();
    }
}

void SwitchButton::enterEvent(QEvent *e) {
    setCursor(Qt::PointingHandCursor);
    QAbstractButton::enterEvent(e);
}

QSize SwitchButton::sizeHint() const {
    return QSize(2 * (_height + margin), _height + 2 * margin);
}

int SwitchButton::offset() {
    return x;
}
void SwitchButton::setOffset(int o) {
    x = o;
    update();
}

void SwitchButton::setChecked(bool checked)
{
    thumb = checked ? QBrush(thumbColor) : QBrush(offColor);
    if(checked != isChecked()) // Prevents repeating slider animation
    {
        if (checked) {
            animation->setStartValue(_height / 2);
            animation->setEndValue(width() - 2 * margin - _height /2);
        }
        else {
            animation->setStartValue(width() - 2 * margin - _height / 2);
            animation->setEndValue(_height / 2);
        }
        animation->start();
    }
    QAbstractButton::setChecked(checked);
}

void SwitchButton::toggle()
{
    setChecked(!isChecked());
}
