/*
 * Copyright (C) Kreogist Dev Team <kreogistdevteam@126.com>
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */
#ifndef KNMUSICTREEVIEWBASE_H
#define KNMUSICTREEVIEWBASE_H

#include "knmusicglobal.h"

#include <QTreeView>

using namespace KNMusic;

class QTimeLine;
class KNConnectionHandler;
class KNMusicSoloMenuBase;
class KNMusicMultiMenuBase;
class KNMusicModelBase;
class KNMusicProxyModel;
class KNMusicProxyModelPool;
class KNMusicTreeViewBase : public QTreeView
{
    Q_OBJECT
public:
    explicit KNMusicTreeViewBase(QWidget *parent = 0);

signals:

public slots:
    virtual void resetHeaderState();

protected:
    void moveToFirst(const int &logicalIndex);

private:
    void configureTimeLine(QTimeLine *timeLine);
    void showSoloMenu(QMouseEvent *event);
    void showMultiMenu(QMouseEvent *event);
    QTimeLine *m_mouseIn, *m_mouseOut;
    KNMusicProxyModel *m_proxyModel=nullptr;
    KNMusicProxyModelPool *m_proxyModelPool;
    KNMusicSoloMenuBase *m_soloMenu=nullptr;
    KNMusicMultiMenuBase *m_multiMenu=nullptr;
    KNConnectionHandler *m_soloConnections, *m_multiConnections;
    QDrag *m_drag;
    QMimeData *m_mimeData;
    QColor m_alternateColor=QColor(255,255,255),
    m_fontColor=QColor(255,255,255),
    m_buttonColor=QColor(255,255,255);
    int m_maxOpacity=0x30,
    m_fontBase=0x9f,
    m_buttonBase=0x10;
    bool m_pressed=true;
};

#endif // KNMUSICTREEVIEWBASE_H