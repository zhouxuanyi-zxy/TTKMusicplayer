/***************************************************************************
 * This file is part of the TTK qmmp plugin project
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

#ifndef FLORID_H
#define FLORID_H

#include <QTimer>
#include "qmmp.h"
#include "visual.h"

#define DISTANCE    100

/*! @brief Helper class to round animation widget.
 * @author Greedysky <greedysky@163.com>
 */
class QMMP_EXPORT RoundAnimationLabel : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit RoundAnimationLabel(QWidget *parent = nullptr);
    ~RoundAnimationLabel();

    /*!
     * Set rotating widget background pixmap.
     */
    void setPixmap(const QPixmap &pix);

public slots:
    /*!
     * Start to rotating widget.
     */
    void start();
    /*!
     * Stop to rotating widget.
     */
    void stop();
    /*!
     * rotating timeout.
     */
    void timeout();

protected:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    QPixmap m_pixmap;
    QTimer m_timer;
    int m_rotateAngle = 0;

};


/*! @brief Helper class to florid widget.
 * @author Greedysky <greedysky@163.com>
 */
class QMMP_EXPORT Florid : public Visual
{
    Q_OBJECT
public:
    /*!
     * Constructor.
     */
    explicit Florid(QWidget *parent = nullptr);
    /*!
     * Destructor.
     */
    virtual ~Florid();

public slots:
    /*!
    * Set background pixmap.
    */
   void setPixmap(const QPixmap &pix);
    /*!
     * Starts visualization.
     */
    virtual void start() override;
    /*!
     * Stops visualization.
     */
    virtual void stop() override;

private slots:
   /*!
    * Current media url changed.
    */
   void mediaUrlChanged();

protected:
    /*!
    * Rerender the image by color burn transform.
    */
    void reRenderImage(QColor &avg, const QImage *input);
    /*!
    * Rerender the image label.
    */
    void reRenderLabel();
    /*!
     * Process current patch visual data by state.
     */
    virtual void processPatch(bool state) override;

    virtual void hideEvent(QHideEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

protected:
    QImage m_image;
    bool m_renderLabel = false;
    QColor m_averageColor = QColor(255, 255, 255);
    bool m_gradientOn = false;
    RoundAnimationLabel *m_roundLabel = nullptr;

};

#endif
