/***************************************************************************
  widget_utils.cpp
  ----------------
  Copyright © 2014-2019, LI-COR Biosciences, Inc. All Rights Reserved.
  Author: Antonio Forgione

  This file is part of EddyPro®.

  NON-COMMERCIAL RESEARCH PURPOSES ONLY - EDDYPRO® is licensed for
  non-commercial academic and government research purposes only,
  as provided in the EDDYPRO® End User License Agreement.
  EDDYPRO® may only be used as provided in the End User License Agreement
  and may not be used or accessed for any commercial purposes.
  You may view a copy of the End User License Agreement in the file
  EULA_NON_COMMERCIAL.rtf.

  Commercial companies that are LI-COR flux system customers are
  encouraged to contact LI-COR directly for our commercial EDDYPRO®
  End User License Agreement.

  EDDYPRO® contains Open Source Components (as defined in the
  End User License Agreement). The licenses and/or notices for the
  Open Source Components can be found in the file LIBRARIES.txt.

  EddyPro® is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "widget_utils.h"

#include <limits>

#include <QApplication>
#include <QCalendarWidget>
#include <QComboBox>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QDesktopServices>
#include <QFontMetrics>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QSettings>
#include <QStyle>
#include <QTextEdit>
#include <QToolButton>
#include <QWidget>

#include <memory>

#include "configstate.h"
#include "defs.h"
#include "docchooser.h"
#include "fileutils.h"
#include "globalsettings.h"

// Test for GCC < 4.9.0
// std::make_unique.h is implemented from GCC >= 4.9.0
#if defined(Q_CC_GNU) && !defined(Q_CC_CLANG)
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#if GCC_VERSION < 40900
#include "make_unique.h"
#endif
#endif // Q_CC_GNU

const QColor WidgetUtils::getColor(int step)
{
    QColor c(170, 230, 255); // #aae6ff
    auto h = c.hue();
    auto s = c.saturation();
    auto v = c.value();

    c.setHsv(abs((h - (step * 10))) % 360, s, v);

    return c;
}

// private helpers
namespace {

// Redraw widget recomputing Qt style-sheet based on Q_PROPERTY
void updateStyle(QWidget* widget)
{
    // update style
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

// NOTE: never used, but possibly useful
//void updatePropertyAndStyle(QWidget* widget,
//                            const char* name,
//                            const QVariant& value)
//{
//    // set property
//    widget->setProperty(name, value);

//    // update the local style
//    updateStyle(widget);
//}

}  // unnamed namespace

void WidgetUtils::updatePropertyListAndStyle(QWidget* widget,
                                             QList<PropertyList> propertyList)
{
    for (const auto &prop : propertyList)
    {
        // set property
        widget->setProperty(prop.first, prop.second);
    }

    // update the local style
    updateStyle(widget);
}

// NOTE: hack useful to trigger tooltip updates
void WidgetUtils::resetComboToItem(QComboBox* combo, int i)
{
    combo->setCurrentIndex(-1);
    combo->setCurrentIndex(i);
}

// set the combo tooltip to the specified item tooltip
void WidgetUtils::updateComboItemTooltip(QComboBox* combo, int i)
{
    combo->setToolTip(combo->itemData(i, Qt::ToolTipRole).toString());
}

// set the line edit tooltip to the current line edit text
void WidgetUtils::updateLineEditToolip(QLineEdit* lineedit)
{
    lineedit->setToolTip(QStringLiteral("%1").arg(lineedit->text()));
}

// return the data of the current combo item
QVariant WidgetUtils::currentComboItemData(QComboBox* combo, int role)
{
    return combo->itemData(combo->currentIndex(), role);
}

// remove the context help button from the widget
// (tipically a dialog or message box)
void WidgetUtils::removeFlagFromWidget(Qt::WindowFlags flag, QWidget* w)
{
    Qt::WindowFlags winFlags = w->windowFlags();
    winFlags &= ~flag;
    w->setWindowFlags(winFlags);
}

// remove the context help button from the widget
// (tipically a dialog or message box)
void WidgetUtils::removeContextHelpButton(QWidget* w)
{
    removeFlagFromWidget(Qt::WindowContextHelpButtonHint, w);
}

// set the text of the label with specified elide mode and width
void WidgetUtils::setElidedTextToLabel(QLabel* label,
                                       const QString& text,
                                       Qt::TextElideMode mode,
                                       int width)
{
    QFontMetrics fm(label->font());
    int realWidth = width - 40;
    auto clippedText = fm.elidedText(text, mode, realWidth);
    label->setText(clippedText);
}

// set the text of the line edit with specified elide mode and width
// NOTE: never used
void WidgetUtils::setElidedTextToLineEdit(QLineEdit* lineEdit,
                                          const QString& text,
                                          Qt::TextElideMode mode,
                                          int width)
{
    QFontMetrics fm(lineEdit->font());
    int realWidth = width - 40;
    auto clippedText = fm.elidedText(text, mode, realWidth);
    lineEdit->setText(clippedText);
}

void WidgetUtils::customizeCalendar(QCalendarWidget* cal)
{
    cal->setVerticalHeaderFormat(QCalendarWidget::ISOWeekNumbers);

    auto btn = cal->findChild<QToolButton *>(QStringLiteral("qt_calendar_prevmonth"));

    QIcon icon_left;
    auto left_arrow_pixmap = QPixmap(QStringLiteral(":/icons/cal-left-arrow"));
//#if defined(Q_OS_MACOS)
//    left_arrow_pixmap.setDevicePixelRatio(2.0);
//#endif
    icon_left.addPixmap(left_arrow_pixmap, QIcon::Normal, QIcon::On);
    btn->setIcon(icon_left);

    btn = cal->findChild<QToolButton *>(QStringLiteral("qt_calendar_nextmonth"));

    QIcon icon_right;
    auto right_arrow_pixmap = QPixmap(QStringLiteral(":/icons/cal-right-arrow"));
//#if defined(Q_OS_MACOS)
//    right_arrow_pixmap.setDevicePixelRatio(2.0);
//#endif
    icon_right.addPixmap(right_arrow_pixmap, QIcon::Normal, QIcon::On);
    btn->setIcon(icon_right);

    cal->setStyleSheet(QStringLiteral(
        "QCalendarView {border: 1px solid #666; padding-bottom: -3px;}"
        "QAbstractItemView {selection-background-color: #318ef4; "
                            "font: normal normal 11px \"Open Sans\"; }"
        "QToolButton:hover {color: black; background: #2B7AE0;}"
        "QToolButton#qt_calendar_monthbutton {padding-right: 15px;}"
        "QToolButton::menu-indicator {"
                               "width: 18px; height: 20px;"
                               "image: url(:/icons/cal-down);}"
        "QToolButton::menu-indicator:pressed,"
        "QToolButton::menu-indicator:open { /*top:10px; left: 10px;*/"
                               "image: url(:/icons/cal-down-pressed);}"));
}

// NOTE: hack to show the calendar,
// because dateEdit->calendarWidget()->show() does not work
void WidgetUtils::showCalendarOf(QWidget* widget)
{
    QCoreApplication::postEvent(widget,
                                new QMouseEvent(QEvent::MouseButtonPress,
                                                QPoint(100.0, 10.0),
                                                Qt::LeftButton,
                                                Qt::NoButton,
                                                Qt::NoModifier));
}

// Append a horizontal rule <hr> to QTextEdit.
// NOTE: never used yet.
void WidgetUtils::appendHrToTextEdit(QTextEdit* te)
{
    auto textCursor = te->textCursor();
    auto blockFmt = textCursor.blockFormat();
    te->append(QLatin1String("<hr>"));
    textCursor.setBlockFormat(blockFmt);
    te->setTextCursor(textCursor);
}

void WidgetUtils::openAppWebsite()
{
    QDesktopServices::openUrl(QUrl(Defs::APP_URL));
}

void WidgetUtils::openForumWebsite()
{
    QDesktopServices::openUrl(QUrl(Defs::APP_FORUM_URL));
}

bool WidgetUtils::okToOverwrite(QWidget* parent, const QString& filename)
{
    return yesNoQuestion(parent,
                    QObject::tr("Overwrite File"),
                    QObject::tr("<p>Are you sure you want to "
                                "overwrite the following file?</p>"),
                    QObject::tr("<p>\"%1\"</p>").arg(filename),
                    QStringLiteral("overwriteMessage"),
                    QObject::tr("Yes"),
                    QObject::tr("Cancel"));
}

bool WidgetUtils::okToRemoveColumn(QWidget* parent)
{
    return yesNoQuestion(parent,
                    QObject::tr("Remove Column"),
                    QObject::tr("Do you want to remove this column?"));
}

QMessageBox::ButtonRole WidgetUtils::requestToSave(QWidget* parent,
                                                   const QString& title,
                                                   const QString& text,
                                                   const QString& infoText)
{
    auto messageBox = std::make_unique<QMessageBox>(parent);

    // macOS compatibility (to look like a sheet)
    if (parent)
    {
        messageBox->setWindowModality(Qt::WindowModal);
    }
    auto pixmap_2x = QPixmap(QStringLiteral(":/icons/msg-question"));
#if defined(Q_OS_MACOS)
    pixmap_2x.setDevicePixelRatio(2.0);
#endif
    messageBox->setIconPixmap(pixmap_2x);
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    if (!infoText.isEmpty())
    {
        messageBox->setInformativeText(infoText);
    }
    messageBox->addButton(QMessageBox::Save);
    messageBox->addButton(QObject::tr("Do &Not Save"), QMessageBox::RejectRole);
    messageBox->addButton(QMessageBox::Cancel);
    messageBox->setEscapeButton(QMessageBox::Cancel);
    messageBox->setDefaultButton(QMessageBox::Save);

    WidgetUtils::removeContextHelpButton(messageBox.get());

    messageBox->exec();
    return messageBox->buttonRole(messageBox->clickedButton());
}

bool WidgetUtils::information(QWidget* parent,
                              const QString& title,
                              const QString& text,
                              const QString& infoText)
{
//    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    auto messageBox = std::make_unique<QMessageBox>(parent);

    // macOS compatibility (to look like a sheet)
    if (parent)
    {
        messageBox->setWindowModality(Qt::WindowModal);
    }
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    if (!infoText.isEmpty())
    {
        messageBox->setInformativeText(infoText);
    }
    auto pixmap_2x = QPixmap(QStringLiteral(":/icons/msg-info"));
#if defined(Q_OS_MACOS)
    pixmap_2x.setDevicePixelRatio(2.0);
#endif
    messageBox->setIconPixmap(pixmap_2x);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->setEscapeButton(QMessageBox::Ok);

//    WidgetUtils::removeContextHelpButton(messageBox.data());
    WidgetUtils::removeContextHelpButton(messageBox.get());

    return messageBox->exec();
}

void WidgetUtils::warning(QWidget* parent,
                          const QString& title,
                          const QString& text,
                          const QString& infoText,
                          const QString& objectName)
{
    auto messageBox = std::make_unique<QMessageBox>(parent);
    messageBox->setObjectName(objectName);

    // macOS compatibility (to look like a sheet)
    if (parent)
    {
        messageBox->setWindowModality(Qt::WindowModal);
    }
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    if (!infoText.isEmpty())
    {
        messageBox->setInformativeText(infoText);
    }
    auto pixmap_2x = QPixmap(QStringLiteral(":/icons/msg-warning"));
#if defined(Q_OS_MACOS)
    pixmap_2x.setDevicePixelRatio(2.0);
#endif
    messageBox->setIconPixmap(pixmap_2x);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->setEscapeButton(QMessageBox::Ok);

    WidgetUtils::removeContextHelpButton(messageBox.get());

    messageBox->exec();
}

void WidgetUtils::critical(QWidget* parent,
                           const QString& title,
                           const QString& text,
                           const QString& infoText)
{
    auto messageBox = std::make_unique<QMessageBox>(parent);

    // macOS compatibility (to look like a sheet)
    if (parent)
    {
        messageBox->setWindowModality(Qt::WindowModal);
    }
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    if (!infoText.isEmpty())
    {
        messageBox->setInformativeText(infoText);
    }
    auto pixmap_2x = QPixmap(QStringLiteral(":/icons/msg-critical"));
#if defined(Q_OS_MACOS)
    pixmap_2x.setDevicePixelRatio(2.0);
#endif
    messageBox->setIconPixmap(pixmap_2x);
        messageBox->addButton(QMessageBox::Ok);
    messageBox->setEscapeButton(QMessageBox::Ok);

    WidgetUtils::removeContextHelpButton(messageBox.get());

    messageBox->exec();
}

bool WidgetUtils::yesNoQuestion(QWidget* parent,
                           const QString& title,
                           const QString& text,
                           const QString& infoText,
                           const QString& objectName,
                           const QString& yesText,
                           const QString& noText)
{
    auto messageBox = std::make_unique<QMessageBox>(parent);
    messageBox->setObjectName(objectName);

    // macOS compatibility (to look like a sheet)
    if (parent)
    {
        messageBox->setWindowModality(Qt::WindowModal);
    }
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    if (!infoText.isEmpty())
    {
        messageBox->setInformativeText(infoText);
    }
    auto pixmap_2x = QPixmap(QStringLiteral(":/icons/msg-question"));
#if defined(Q_OS_MACOS)
    pixmap_2x.setDevicePixelRatio(2.0);
#endif
    messageBox->setIconPixmap(pixmap_2x);
    QPushButton *yesButton = messageBox->addButton(yesText,
            QMessageBox::AcceptRole);
    QPushButton* noButton = messageBox->addButton(noText, QMessageBox::RejectRole);
    messageBox->setEscapeButton(noButton);
    messageBox->setDefaultButton(yesButton);

    WidgetUtils::removeContextHelpButton(messageBox.get());

    messageBox->exec();
    return (messageBox->clickedButton() == yesButton);
}

void WidgetUtils::showHelp(const QUrl& url)
{
    // read state
    auto autoChooseHelp = GlobalSettings::getAppPersistentSettings(
                Defs::CONFGROUP_WINDOW,
                Defs::CONF_WIN_AUTOHELP, false).toBool();
    auto offlineHelp = GlobalSettings::getAppPersistentSettings(
                Defs::CONFGROUP_WINDOW,
                Defs::CONF_WIN_OFFLINEHELP, false).toBool();

    qDebug() << "autoChooseHelp" << autoChooseHelp;
    qDebug() << "offlineHelp" << offlineHelp;

    if (autoChooseHelp)
    {
        if (!offlineHelp)
        {
            // browse online help version
            qDebug() << "online url" << url << QDesktopServices::openUrl(url);
        }
        else
        {
            qDebug() << "offline url" << url;

            // open local help
            auto htmlHelpPath = QApplication::applicationDirPath();
            auto localUrlString = QString();

            if (url.toString().contains(QStringLiteral("home")))
            {
                 htmlHelpPath = htmlHelpPath + QStringLiteral("/docs/support/EddyPro/home.html");
            }
            else if (url.toString().contains(QStringLiteral("qmhucid6g0hdvd3d13tk")))
            {
                 htmlHelpPath = htmlHelpPath + QStringLiteral("/docs/EddyPro_QuickStart_12756.pdf");
            }
            else if (url.toString().contains(QStringLiteral("1ium2zmwm6hl36yz9bu4")))
            {
                 htmlHelpPath = htmlHelpPath + QStringLiteral("/docs/EddyPro_Manual_12025.pdf");
            }
            else if (url.toString().contains(QStringLiteral("videos")))
            {
                 htmlHelpPath = htmlHelpPath + QStringLiteral("/docs/support/EddyPro/videos.html");
            }
            else
            {
                localUrlString = url.toString(QUrl::RemoveAuthority
                    | QUrl::RemoveScheme).remove(QStringLiteral("/env"));
                htmlHelpPath = htmlHelpPath + QStringLiteral("/docs") + localUrlString;
            }

            auto localUrl = QUrl();

            if (htmlHelpPath.contains(QStringLiteral("#")))
            {
                auto localUrlHost = htmlHelpPath.section(QLatin1Char('#'), 0, 0);
                auto localUrlFragment = htmlHelpPath.section(QLatin1Char('#'), 1, 1);
                localUrl = QUrl::fromLocalFile(localUrlHost);
                localUrl.setFragment(localUrlFragment);
            }
            else
            {
                localUrl = QUrl::fromLocalFile(htmlHelpPath);
            }

            qDebug() << "local url" << localUrl;
            QDesktopServices::openUrl(localUrl);
        }
    }
    else
    {
        DocChooserDialog docChooser(url);
        docChooser.exec();
    }
}

void WidgetUtils::setProgressValue(QProgressBar* bar, int value)
{
    auto boundValue = qBound(bar->minimum(),
                            value,
                            bar->maximum());
    bar->setValue(boundValue);
}

QScrollArea *WidgetUtils::getContainerScrollArea(QWidget* parent, QLayout* layout)
{
    auto frame = new QWidget(parent);
    frame->setLayout(layout);
    frame->setProperty("scrollContainerWidget", true);
    frame->setMinimumWidth(frame->sizeHint().width());

    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(frame);
    scrollArea->setWidgetResizable(true);
    return scrollArea;
}

QString WidgetUtils::getSearchPathHint(/*ConfigState *config*/)
{
    // default search path
    auto searchPath = QDir::homePath();
    auto lastDataPath = GlobalSettings::getAppPersistentSettings(
                       Defs::CONFGROUP_WINDOW,
                       Defs::CONF_WIN_LAST_DATAPATH, QString()).toString();

    if (!lastDataPath.isEmpty() && FileUtils::existsPath(lastDataPath))
    {
        searchPath = lastDataPath;
    }

    return searchPath;
}

bool WidgetUtils::okToCloseSmartFlux(QWidget* parent)
{
    return yesNoQuestion(parent,
                         QObject::tr("Close SmartFlux Configuration"),
                         QObject::tr("Do you want to leave the SmartFlux Configuration?"));
}

QPushButton *WidgetUtils::createCommonButton(QWidget* parent, const QString& text)
{
    auto button = new QPushButton(parent);
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    button->setDefault(true);
    button->setProperty("mdButton", true);
    return button;
}

QLabel *WidgetUtils::createBlueLabel(QWidget *parent, const QString& text)
{
    auto label = new QLabel(parent);
    label->setText(text);
    label->setProperty("blueLabel", true);
    return label;
}
