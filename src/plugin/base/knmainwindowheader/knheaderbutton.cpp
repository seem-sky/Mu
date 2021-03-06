/*
 * Copyright (C) Kreogist Dev Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <QTimeLine>
#include <QRadialGradient>
#include <QGraphicsOpacityEffect>
#include <QLabel>

#include "knheaderbutton.h"

#include <QDebug>

KNHeaderButton::KNHeaderButton(QWidget *parent) :
    KNAnimeCheckedButton(parent)
{
    //Set properties.
    setContentsMargins(0,0,0,0);
    setMinimumWidth(182);

    //Connect signal.
    connect(this, &KNHeaderButton::clicked,
            this, &KNHeaderButton::requireShowCategorySwitcher);

    //Set palette.
    configurePalette();

    //Inital widgets.
    initialIcon();
    initialText();
    initialTimeLine();
}

void KNHeaderButton::setIcon(const QPixmap &pixmap)
{
    m_icon->setPixmap(pixmap.scaled(m_iconSize,
                                    m_iconSize,
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation));
}

void KNHeaderButton::setText(const QString &text)
{
    //Update the text.
    m_text->setText(text);
    //Resize the text.
    m_text->resize(m_text->fontMetrics().width(text),
                   m_text->fontMetrics().height());
    //Resize the button size.
    updateWidth();
}

QPixmap KNHeaderButton::icon() const
{
    return *m_icon->pixmap();
}

QString KNHeaderButton::text() const
{
    return m_text->text();
}

void KNHeaderButton::restoreButtonState()
{
    //Unfreeze button.
    setChecked(false);
    //Using mouse out anime to restore the geometry.
    startMouseOutAnime();
}

void KNHeaderButton::onActionMouseAnimation(const int &frame)
{
    //Move icon label.
    qreal moved=(qreal)qAbs(frame-m_iconX);
    m_icon->move(frame, m_iconY);
    //Move text label.
    m_text->move(m_leftMargin, m_textY-moved/4);
    //Set text gradient.
    qreal alphaPrefer=moved/m_iconMoved;
    m_opacityColor.setAlphaF(alphaPrefer>1.0?1.0:alphaPrefer);
    m_textGradient.setColorAt(1, m_opacityColor);
    m_textEffect->setOpacityMask(m_textGradient);
    m_text->setGraphicsEffect(m_textEffect);
}

void KNHeaderButton::onActionMouseDownUpAnimation(const int &frame)
{
    //Move icon label.
    m_icon->move(frame, m_iconY);
    //Move text label.
    m_text->move(m_leftMargin, m_textY+(frame-m_iconX)/2);
}

inline void KNHeaderButton::configurePalette()
{
    QPalette pal=palette();
    pal.setColor(QPalette::WindowText, QColor(0xff,0xff,0xff));
    setPalette(pal);
}

inline void KNHeaderButton::initialTimeLine()
{
    //Initial text anime(geometry).
    m_mouseIn=generateTimeline(m_iconMouseInX);
    connect(m_mouseIn, &QTimeLine::frameChanged,
            this, &KNHeaderButton::onActionMouseAnimation);

    m_mouseOut=generateTimeline(m_iconX);
    connect(m_mouseOut, &QTimeLine::frameChanged,
            this, &KNHeaderButton::onActionMouseAnimation);

    m_mouseDown=generateTimeline(-m_iconSize);
    connect(m_mouseDown, &QTimeLine::frameChanged,
            this, &KNHeaderButton::onActionMouseDownUpAnimation);

    m_mouseUp=generateTimeline(m_iconMouseUpX);
    connect(m_mouseUp, &QTimeLine::frameChanged,
            this, &KNHeaderButton::onActionMouseDownUpAnimation);
}

inline void KNHeaderButton::initialIcon()
{
    //Initial the icon displayer.
    m_icon=new QLabel(this);
    m_icon->setScaledContents(true);
    m_icon->setFixedSize(m_iconSize, m_iconSize);
    m_icon->move(m_iconX, m_iconY);
}

inline void KNHeaderButton::initialText()
{
    //Initial the text displayer.
    m_text=new QLabel(this);
    m_text->move(m_leftMargin, m_textY);
    //Configure the palette.
    QPalette pal=m_text->palette();
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    m_text->setPalette(pal);
    //Configure the font.
    m_textFont=m_text->font();
    m_textFont.setBold(true);
    m_textFont.setPixelSize(m_textSize);
    m_text->setFont(m_textFont);
    //Update font metrics data.
    m_text->fontMetrics();
    //Initial the graphic effects.
    m_textEffect=new QGraphicsOpacityEffect(m_text);
    m_textEffect->setOpacity(0.7);
    m_textGradient=QLinearGradient(QPointF(0,0),
                                   QPointF(0,50));
    m_textGradient.setColorAt(0, QColor(0,0,0,m_textAlpha));
    m_textGradient.setColorAt(1, m_opacityColor);
    m_textEffect->setOpacityMask(m_textGradient);
    m_text->setGraphicsEffect(m_textEffect);
}

inline QTimeLine *KNHeaderButton::generateTimeline(const int &endFrame)
{
    QTimeLine *timeline=new QTimeLine(200, this);
    timeline->setEasingCurve(QEasingCurve::OutCubic);
    timeline->setUpdateInterval(16);
    timeline->setEndFrame(endFrame);
    return timeline;
}

void KNHeaderButton::startMouseInAnime()
{
    //Stop all the animation.
    m_mouseOut->stop();
    m_mouseIn->stop();
    //Set current position
    m_mouseIn->setStartFrame(m_icon->x());
    //Start mouse in animation.
    m_mouseIn->start();
}

void KNHeaderButton::startMouseOutAnime()
{
    //Stop all the animation.
    m_mouseOut->stop();
    m_mouseIn->stop();
    //Set current position
    m_mouseOut->setStartFrame(m_icon->x());
    //Start mouse in animation.
    m_mouseOut->start();
}

void KNHeaderButton::startMouseDownAnime()
{
    //Stop up and down animations.
    m_mouseUp->stop();
    m_mouseDown->stop();
    //Set start parameter.
    m_mouseDown->setStartFrame(m_icon->x());
    //Start animation.
    m_mouseDown->start();
}

void KNHeaderButton::startMouseUpAnime()
{
    //Stop up and down animations.
    m_mouseDown->stop();
    m_mouseUp->stop();
    //Set start parameter.
    m_mouseUp->setStartFrame(m_icon->x());
    //Start animation.
    m_mouseUp->start();
}

inline void KNHeaderButton::updateWidth()
{
    //Update the size.
    resize(m_text->fontMetrics().width(m_text->text())+m_leftMargin,
           height());
    //Ask to resize the space to fit the width.
    emit requireSetLeftSpacing(width());
}
