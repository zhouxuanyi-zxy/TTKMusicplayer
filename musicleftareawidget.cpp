#include "musicleftareawidget.h"
#include "ui_musicapplication.h"
#include "musicuiobject.h"
#include "musictoolsetswidget.h"
#include "musicmydownloadrecordwidget.h"
#include "musicwebradiolistview.h"
#include "musicspectrumwidget.h"

MusicLeftAreaWidget::MusicLeftAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_stackedWidget = NULL;
    m_musicSpectrumWidget = NULL;
}

MusicLeftAreaWidget::~MusicLeftAreaWidget()
{
    delete m_stackedWidget;
    delete m_musicSpectrumWidget;
}

void MusicLeftAreaWidget::setupUi(Ui::MusicApplication* ui)
{
    m_ui = ui;
    connect(ui->musicKey,SIGNAL(clicked()),parent(),SLOT(musicKey()));
    connect(ui->musicPrivious,SIGNAL(clicked()),parent(),SLOT(musicPlayPrivious()));
    connect(ui->musicNext,SIGNAL(clicked()),parent(),SLOT(musicPlayNext()));
    connect(ui->musicSound,SIGNAL(clicked()),parent(),SLOT(musicVolumeNULL()));
    connect(ui->musicSoundSlider,SIGNAL(valueChanged(int)),parent(),SLOT(musicVolumeChanged(int)));
    connect(ui->musicBestLove,SIGNAL(clicked()),parent(),SLOT(musicAddSongToLovestListAt()));
    connect(ui->music3DPlayButton,SIGNAL(clicked()),parent(),SLOT(musicSetPlay3DMusic()));
    connect(ui->musicButton_playlist,SIGNAL(clicked()), this, SLOT(musicStackedSongListWidgetChanged()));
    connect(ui->musicButton_tools,SIGNAL(clicked()), this, SLOT(musicStackedToolsWidgetChanged()));
    connect(ui->musicButton_radio,SIGNAL(clicked()), this, SLOT(musicStackedRadioWidgetChanged()));
    connect(ui->musicButton_mydownl,SIGNAL(clicked()), this, SLOT(musicStackedMyDownWidgetChanged()));

    ui->musicPrivious->setIcon(QIcon(QString::fromUtf8(":/image/privious")));
    ui->musicNext->setIcon(QIcon(QString::fromUtf8(":/image/next")));
    ui->musicKey->setIcon(QIcon(QString::fromUtf8(":/image/play")));
    ui->musicBestLove->setIcon(QIcon(QString::fromUtf8(":/image/bestlove")));
    ui->music3DPlayButton->setIcon(QIcon(QString::fromUtf8(":/equalizer/3doff")));
    ui->musicButton_cloud->setIcon(QIcon(QString::fromUtf8(":/image/buttoncloud")));
    ui->musicButton_mydownl->setIcon(QIcon(QString::fromUtf8(":/image/buttonmydownl")));
    ui->musicButton_playlist->setIcon(QIcon(QString::fromUtf8(":/image/buttonplaylist")));
    ui->musicButton_radio->setIcon(QIcon(QString::fromUtf8(":/image/buttonradio")));
    ui->musicButton_tools->setIcon(QIcon(QString::fromUtf8(":/image/buttontools")));
    ui->musicPrivious->setIconSize(QSize(45,45));
    ui->musicNext->setIconSize(QSize(45,45));
    ui->musicKey->setIconSize(QSize(45,45));
    ui->musicBestLove->setIconSize(QSize(25,25));
    ui->music3DPlayButton->setIconSize(QSize(40,20));
    ui->musicButton_cloud->setIconSize(QSize(35,35));
    ui->musicButton_mydownl->setIconSize(QSize(35,35));
    ui->musicButton_playlist->setIconSize(QSize(35,35));
    ui->musicButton_radio->setIconSize(QSize(35,35));
    ui->musicButton_tools->setIconSize(QSize(35,35));
    ui->musicPlayMode->setIconSize(QSize(25,25));

    ui->musicSoundSlider->setStyleSheet(MusicUIObject::MSliderStyle01);
    ui->musicPrivious->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicNext->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicKey->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicBestLove->setStyleSheet(MusicUIObject::MToolButtonStyle05);
    ui->musicDesktopLrc->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->music3DPlayButton->setStyleSheet(MusicUIObject::MToolButtonStyle05);
    ui->musicButton_cloud->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicButton_mydownl->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicButton_playlist->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicButton_radio->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicButton_tools->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    ui->musicPlayMode->setStyleSheet(MusicUIObject::MToolButtonStyle02);

    ui->musicPrivious->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicKey->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicNext->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicSound->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicSoundSlider->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicBestLove->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicPlayMode->setCursor(QCursor(Qt::PointingHandCursor));

    ui->windowClose->setToolTip(tr("Close"));
    ui->musicKey->setToolTip(tr("Play"));
    ui->musicPrivious->setToolTip(tr("Privious"));
    ui->musicNext->setToolTip(tr("Next"));
    ui->musicBestLove->setToolTip(tr("bestlove"));
    ui->musicButton_cloud->setToolTip(tr("musicCloud"));
    ui->musicButton_mydownl->setToolTip(tr("musicMydownl"));
    ui->musicButton_playlist->setToolTip(tr("musicPlaylist"));
    ui->musicButton_radio->setToolTip(tr("musicRadio"));
    ui->musicButton_tools->setToolTip(tr("musicTools"));
}

void MusicLeftAreaWidget::musicStackedSongListWidgetChanged()
{
    m_ui->songsContainer->setCurrentIndex(0);
}

void MusicLeftAreaWidget::musicStackedToolsWidgetChanged()
{
    delete m_stackedWidget;
    m_stackedWidget = new MusicToolSetsWidget(this);

    m_ui->songsContainer->addWidget(m_stackedWidget);
    connect(m_stackedWidget, SIGNAL(setSpectrum(HWND,int,int)), parent(),
                             SLOT(setSpectrum(HWND,int,int)));
    connect(m_stackedWidget, SIGNAL(timerParameterChanged()), parent(),
                             SLOT(musicToolSetsParameter()));
    connect(m_stackedWidget, SIGNAL(addSongToPlay(QStringList)), parent(),
                             SLOT(addSongToPlayList(QStringList)));
    connect(m_stackedWidget, SIGNAL(getCurrentPlayList(QStringList&)), parent(),
                             SLOT(getCurrentPlayList(QStringList&)));
    m_ui->songsContainer->setCurrentIndex(1);
}

void MusicLeftAreaWidget::musicStackedMyDownWidgetChanged()
{
    delete m_stackedWidget;
    m_stackedWidget = new MusicMyDownloadRecordWidget(this);
    connect(static_cast<MusicMyDownloadRecordWidget*>(m_stackedWidget),SIGNAL(musicPlay(QStringList)), parent(), 
                                                                       SLOT(addSongToPlayList(QStringList)));
    m_ui->songsContainer->addWidget(m_stackedWidget);
    m_ui->songsContainer->setCurrentIndex(1);
}

void MusicLeftAreaWidget::musicStackedRadioWidgetChanged()
{
    delete m_stackedWidget;
    m_stackedWidget = new MusicWebRadioListView(this);

    m_ui->songsContainer->addWidget(m_stackedWidget);
    m_ui->songsContainer->setCurrentIndex(1);
}

void MusicLeftAreaWidget::musicSpectrumWidget()
{
    if(m_musicSpectrumWidget == NULL)
    {
        m_musicSpectrumWidget = new MusicSpectrumWidget;
    }
    m_musicSpectrumWidget->show();
    connect(m_musicSpectrumWidget,SIGNAL(setSpectrum(HWND,int,int)),
                        parent(), SLOT(setSpectrum(HWND,int,int)));
}
