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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KNMAINWINDOW_H
#define KNMAINWINDOW_H

#include "knmainwindowplugin.h"

class KNMainWindowContainer;
class KNMainWindow : public KNMainWindowPlugin
{
    Q_OBJECT
public:
    explicit KNMainWindow(QObject *parent = 0);
    void addCategoryPlugin(KNCategoryPlugin *plugin);
    void addHeaderWidget(QWidget *widget);
    void addCentralWidget(QWidget *widget);

signals:

public slots:
    void retranslate();
    void setMainWindow(QMainWindow *mainWindow);
    void setHeader(KNMainWindowHeaderPlugin *plugin);
    void setHeaderIcon(const QPixmap &icon);
    void setHeaderText(const QString &text);
    void setCategoryStack(KNMainWindowCategoryStackPlugin *widget);
    void setCategorySwitcher(KNMainWindowCategorySwitcherPlugin *plugin);
    void setPreferencePanel(KNPreferencePlugin *plugin);
    void showPreference();
    void hidePreference();

private:
    struct CategoryPluginItem
    {
        int index;
        KNCategoryPlugin *plugin;
    };
    QList<CategoryPluginItem> m_categoryList;
    int m_currentCategory=-1;

    //Elements pointers
    QMainWindow *m_mainWindow=nullptr;
    KNMainWindowContainer *m_container;
    KNMainWindowHeaderPlugin *m_headerPlugin=nullptr;
    KNMainWindowCategoryStackPlugin *m_categoryStackPlugin=nullptr;
    KNMainWindowCategorySwitcherPlugin *m_categorySwitcherPlugin=nullptr;
    KNPreferencePlugin *m_preferencePlugin=nullptr;
};

#endif // KNMAINWINDOW_H
