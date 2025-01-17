#ifndef MUSICDOWNLOADMGMTWIDGET_H
#define MUSICDOWNLOADMGMTWIDGET_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "musicabstractmovewidget.h"
#include "musicabstractqueryrequest.h"

namespace Ui {
class MusicDownloadResetWidget;
}

/*! @brief The class of the download file exist widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicDownloadResetWidget : public MusicAbstractMoveWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicDownloadResetWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadResetWidget(QWidget *parent = nullptr);
    ~MusicDownloadResetWidget();

    /*!
     * Set current name to search and download musics.
     */
    void setSongName(const QString &name);

Q_SIGNALS:
    /*!
     * To open stacked download widget once.
     */
    void openStackedDownloadWidget();

public Q_SLOTS:
    /*!
     * Override show function.
     */
    void show();
    /*!
     * Restart to dwonload music data.
     */
    void restartToDownload();
    /*!
     * Open file details information by song.
     */
    void openDetailInfo();
    /*!
     * Open file location in dir.
     */
    void openFileLocation();

protected:
    Ui::MusicDownloadResetWidget* m_ui;

    QWidget *m_parentClass;
    QString m_currentName;

};


/*! @brief The class of the download manager widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicDownloadMgmtWidget : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicDownloadMgmtWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadMgmtWidget(QObject *parent = nullptr);

    /*!
     * Set current name to search and download musics.
     */
    void setSongName(const QString &name, MusicAbstractQueryRequest::QueryType type);

protected:
    QWidget *m_parentClass;

};

#endif // MUSICDOWNLOADMGMTWIDGET_H
