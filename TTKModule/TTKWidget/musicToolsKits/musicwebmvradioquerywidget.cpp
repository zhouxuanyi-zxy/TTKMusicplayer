#include "musicwebmvradioquerywidget.h"
#include "musicwebmvradioquerycategorypopwidget.h"
#include "musicwebmvradioinfowidget.h"
#include "musicmvradiocategoryrequest.h"
#include "musicdownloadsourcerequest.h"
#include "musictinyuiobject.h"
#include "musicimageutils.h"

#define WIDTH_LABEL_SIZE   150
#define HEIGHT_LABEL_SIZE  100
#define LINE_SPACING_SIZE  200

MusicWebMVRadioQueryItemWidget::MusicWebMVRadioQueryItemWidget(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(WIDTH_LABEL_SIZE, HEIGHT_LABEL_SIZE);

    m_playButton = new QPushButton(this);
    m_playButton->setGeometry((WIDTH_LABEL_SIZE - 30) / 2, (HEIGHT_LABEL_SIZE - 30) / 2, 30, 30);
    m_playButton->setCursor(Qt::PointingHandCursor);
    m_playButton->setStyleSheet(MusicUIObject::MQSSTinyBtnPlaylist);
    connect(m_playButton, SIGNAL(clicked()), SLOT(currentItemClicked()));

#ifdef Q_OS_UNIX
    m_playButton->setFocusPolicy(Qt::NoFocus);
#endif

    m_iconLabel = new QLabel(this);
    m_iconLabel->setGeometry(0, 0, WIDTH_LABEL_SIZE, WIDTH_LABEL_SIZE);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setAlignment(Qt::AlignCenter);
    m_nameLabel->setGeometry(0, 0, WIDTH_LABEL_SIZE, HEIGHT_LABEL_SIZE);
    m_nameLabel->setStyleSheet(MusicUIObject::MQSSColorStyle01 + MusicUIObject::MQSSFontStyle05 + MusicUIObject::MQSSFontStyle01);
    m_nameLabel->setText(" - ");
}

MusicWebMVRadioQueryItemWidget::~MusicWebMVRadioQueryItemWidget()
{
    delete m_playButton;
    delete m_iconLabel;
    delete m_nameLabel;
}

void MusicWebMVRadioQueryItemWidget::setMusicResultsItem(const MusicResultsItem &item)
{
    m_itemData = item;
    m_nameLabel->setToolTip(item.m_name);
    m_nameLabel->setText(MusicUtils::Widget::elidedText(m_nameLabel->font(), m_nameLabel->toolTip(), Qt::ElideRight, WIDTH_LABEL_SIZE));

    MusicDownloadSourceRequest *download = new MusicDownloadSourceRequest(this);
    connect(download, SIGNAL(downLoadRawDataChanged(QByteArray)), SLOT(downLoadFinished(QByteArray)));
    if(!item.m_coverUrl.isEmpty() && item.m_coverUrl != COVER_URL_NULL)
    {
        download->startToDownload(item.m_coverUrl);
    }

    m_playButton->hide();
}

void MusicWebMVRadioQueryItemWidget::downLoadFinished(const QByteArray &data)
{
    QPixmap pix;
    pix.loadFromData(data);
    if(!pix.isNull())
    {
        QPixmap cv(":/image/lb_album_cover");
        cv = cv.scaled(m_iconLabel->size());
        pix = pix.scaled(m_iconLabel->size());
        MusicUtils::Image::fusionPixmap(pix, cv, QPoint(0, 0));
        m_iconLabel->setPixmap(pix);
    }

    m_playButton->raise();
}

void MusicWebMVRadioQueryItemWidget::currentItemClicked()
{
    Q_EMIT currentItemClicked(m_itemData);
}

void MusicWebMVRadioQueryItemWidget::enterEvent(QEvent *event)
{
    QLabel::enterEvent(event);

    m_playButton->show();
    m_nameLabel->hide();
}

void MusicWebMVRadioQueryItemWidget::leaveEvent(QEvent *event)
{
    QLabel::leaveEvent(event);

    m_playButton->hide();
    m_nameLabel->show();
}



MusicWebMVRadioQueryWidget::MusicWebMVRadioQueryWidget(QWidget *parent)
    : MusicAbstractItemQueryWidget(parent)
{
    m_container->show();
    layout()->removeWidget(m_mainWindow);
    layout()->addWidget(m_container);
    m_container->addWidget(m_mainWindow);

    m_firstInit = false;
    m_infoWidget = nullptr;
    m_gridLayout = nullptr;
    m_categoryButton = nullptr;

    m_downloadRequest = new MusicMVRadioCategoryRequest(this);
    connect(m_downloadRequest, SIGNAL(createCategoryItem(MusicResultsItem)), SLOT(createCategoryItem(MusicResultsItem)));
}

MusicWebMVRadioQueryWidget::~MusicWebMVRadioQueryWidget()
{
    delete m_infoWidget;
    delete m_gridLayout;
    delete m_categoryButton;
    delete m_downloadRequest;
}

void MusicWebMVRadioQueryWidget::setSongName(const QString &name)
{
    MusicAbstractItemQueryWidget::setSongName(name);
    m_downloadRequest->startToSearch(MusicAbstractQueryRequest::OtherQuery, QString());
}

void MusicWebMVRadioQueryWidget::setSongNameById(const QString &id)
{
    Q_UNUSED(id);
}

void MusicWebMVRadioQueryWidget::resizeWindow()
{
    if(m_infoWidget)
    {
        m_infoWidget->resizeWindow();
    }

    if(!m_resizeWidgets.isEmpty() && m_gridLayout)
    {
        for(int i=0; i<m_resizeWidgets.count(); ++i)
        {
            m_gridLayout->removeWidget(m_resizeWidgets[i]);
        }

        const int lineNumber = width() / LINE_SPACING_SIZE;
        for(int i=0; i<m_resizeWidgets.count(); ++i)
        {
            m_gridLayout->addWidget(m_resizeWidgets[i], i/lineNumber, i%lineNumber, Qt::AlignCenter);
        }
    }
}

void MusicWebMVRadioQueryWidget::createCategoryItem(const MusicResultsItem &item)
{
    if(!m_firstInit)
    {
        delete m_statusLabel;
        m_statusLabel = nullptr;

        m_container->removeWidget(m_mainWindow);
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setStyleSheet(MusicUIObject::MQSSScrollBarStyle01);
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setAlignment(Qt::AlignLeft);
        scrollArea->setWidget(m_mainWindow);
        m_container->addWidget(scrollArea);

        m_firstInit = true;
        QHBoxLayout *mainlayout = TTKStatic_cast(QHBoxLayout*, m_mainWindow->layout());
        QWidget *containTopWidget = new QWidget(m_mainWindow);
        QHBoxLayout *containTopLayout  = new QHBoxLayout(containTopWidget);
        containTopLayout->setContentsMargins(30, 0, 30, 0);
        m_categoryButton = new MusicWebMVRadioQueryCategoryPopWidget(m_mainWindow);
        m_categoryButton->setCategory(MUSIC_MOVIE_RADIO, this);
        containTopLayout->addWidget(m_categoryButton);
        containTopLayout->addStretch(1);
        containTopWidget->setLayout(containTopLayout);

        QFrame *line = new QFrame(m_mainWindow);
        line->setFrameShape(QFrame::HLine);
        line->setStyleSheet(MusicUIObject::MQSSColorStyle06);

        QWidget *containWidget = new QWidget(m_mainWindow);
        m_gridLayout = new QGridLayout(containWidget);
        m_gridLayout->setVerticalSpacing(35);
        containWidget->setLayout(m_gridLayout);

        mainlayout->addWidget(containTopWidget);
        mainlayout->addWidget(line);
        mainlayout->addWidget(containWidget);

        mainlayout->addStretch(1);
    }

    MusicWebMVRadioQueryItemWidget *label = new MusicWebMVRadioQueryItemWidget(this);
    connect(label, SIGNAL(currentItemClicked(MusicResultsItem)), SLOT(currentRadioClicked(MusicResultsItem)));
    label->setMusicResultsItem(item);

    const int lineNumber = width() / LINE_SPACING_SIZE;
    m_gridLayout->addWidget(label, m_resizeWidgets.count() / lineNumber, m_resizeWidgets.count() % lineNumber, Qt::AlignCenter);
    m_resizeWidgets << label;
}

void MusicWebMVRadioQueryWidget::currentRadioClicked(const MusicResultsItem &item)
{
    delete m_infoWidget;
    m_infoWidget = new MusicWebMVRadioInfoWidget(this);
    connect(m_infoWidget, SIGNAL(backToMainMenu()), SLOT(backToMainMenuClicked()));
    m_infoWidget->setSongName(item.m_id);

    m_container->addWidget(m_infoWidget);
    m_container->setCurrentIndex(PLAYLIST_WINDOW_INDEX_1);
}

void MusicWebMVRadioQueryWidget::backToMainMenuClicked()
{
    m_container->setCurrentIndex(PLAYLIST_WINDOW_INDEX_0);
}

void MusicWebMVRadioQueryWidget::categoryChanged(const MusicResultsCategoryItem &category)
{
    if(m_categoryButton)
    {
        m_songNameFull.clear();
        m_categoryButton->setText(category.m_name);
        m_categoryButton->closeMenu();

        while(!m_resizeWidgets.isEmpty())
        {
            QWidget *w = m_resizeWidgets.takeLast();
            m_gridLayout->removeWidget(w);
            delete w;
        }
        m_downloadRequest->startToSearch(MusicAbstractQueryRequest::OtherQuery, category.m_id);
    }
}