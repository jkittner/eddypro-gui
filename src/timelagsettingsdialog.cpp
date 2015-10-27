/***************************************************************************
  timelagsettingsdialog.cpp
  -------------------
  Copyright (C) 2013-2015, LI-COR Biosciences
  Author: Antonio Forgione

  This file is part of EddyPro (R).

  EddyPro (R) is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  EddyPro (R) is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with EddyPro (R). If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "timelagsettingsdialog.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QDateEdit>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>

#include "ancillaryfiletest.h"
#include "clicklabel.h"
#include "configstate.h"
#include "customclearlineedit.h"
#include "dbghelper.h"
#include "ecproject.h"
#include "filebrowsewidget.h"
#include "fileutils.h"
#include "globalsettings.h"
#include "widget_utils.h"

TimeLagSettingsDialog::TimeLagSettingsDialog(QWidget *parent, EcProject *ecProject, ConfigState* config) :
    QDialog(parent),
    ecProject_(ecProject),
    configState_(config)
{
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("Time Lag Optimization Settings"));
    WidgetUtils::removeContextHelpButton(this);

    auto groupTitle = new QLabel;
    groupTitle->setText(tr("Configure smart time lag detection, "
                           "providing quality selection criteria and initial "
                           "time lag windows"));

    auto hrLabel = new QLabel;
    hrLabel->setObjectName(QStringLiteral("hrLabel"));

    existingRadio = new QRadioButton(tr("Time lag file available : "));
    existingRadio->setToolTip(tr("<b>Time lag file available:</b> If you have a satisfactory time lag assessment from a previous run and it applies to the current dataset, you can use it by providing the path to the file 'eddypro_timelag_opt_ID.txt' that was generated by EddyPro in the previous run and contains the results of the assessment. This will shorten program execution time and assure full comparability between the current and previous results."));

    nonExistingRadio = new QRadioButton(tr("Time lag file not available :"));
    nonExistingRadio->setToolTip(tr("<b>Time lag file not available:</b> Choose this option and provide the following information if you need to optimize time lags for your dataset. EddyPro will complete the time lag optimization first and then complete the raw data processing and flux computation procedures."));

    subsetCheckBox = new QCheckBox;
    subsetCheckBox->setProperty("subperiod", true);
    subsetCheckBox->setText(tr("Select a different period"));
    subsetCheckBox->setToolTip(tr("<b>Select a different period:</b> Select this option and set the corresponding dates, to identify the time period EddyPro will use for the Time lag optimization. This subperiod must fall within the time period defined by the available raw data."));

    startDateLabel = new ClickLabel(this);
    startDateLabel->setText(tr("Start :"));
    startDateLabel->setToolTip(tr("<b>Start:</b> Starting date of the time period to be used for time lag optimization. This time should not be shorter than about 1-2 months. As a general recommendation, select a time period during which the instrument setup did not undergo major modifications. Results obtained using a given time period (e.g., 2 months) can be used for processing a longer time period, in which major modifications did not occur in the setup. The stricter the threshold setup in this dialogue, the longer the period should be in order to get robust results."));
    startDateEdit = new QDateEdit;
    startDateEdit->setToolTip(startDateLabel->toolTip());
    startDateEdit->setCalendarPopup(true);
    WidgetUtils::customizeCalendar(startDateEdit->calendarWidget());

    startTimeEdit = new QTimeEdit;
    startTimeEdit->setDisplayFormat(QStringLiteral("hh:mm"));
    startTimeEdit->setAccelerated(true);

    lockedIcon = new QLabel;
    auto pixmap = QPixmap(QStringLiteral(":/icons/vlink-locked"));
#if defined(Q_OS_MAC)
    pixmap.setDevicePixelRatio(2.0);
#endif
    lockedIcon->setPixmap(pixmap);

    endDateLabel = new ClickLabel(this);
    endDateLabel->setText(tr("End :"));
    endDateLabel->setToolTip(tr("<b>End:</b> End date of the time period to be used for time lag optimization. This time should not be shorter than about 1-2 months As a general recommendation, select a time period during which the instrumental setup did not undergo major modifications. Results obtained using a given time period (e.g., 2 months) can be used for processing a longer time period, in which major modifications did not occur in the setup. The stricter the threshold setup in this dialogue, the longer the period should be in order to get robust results."));
    endDateEdit = new QDateEdit;
    endDateEdit->setToolTip(endDateLabel->toolTip());
    endDateEdit->setCalendarPopup(true);
    WidgetUtils::customizeCalendar(endDateEdit->calendarWidget());

    endTimeEdit = new QTimeEdit;
    endTimeEdit->setDisplayFormat(QStringLiteral("hh:mm"));
    endTimeEdit->setAccelerated(true);

    auto dateTimeContainer = new QGridLayout;
    dateTimeContainer->addWidget(startDateEdit, 0, 1);
    dateTimeContainer->addWidget(startTimeEdit, 0, 2);
    dateTimeContainer->addWidget(lockedIcon, 0, 0, 2, 1);
    dateTimeContainer->addWidget(endDateEdit, 1, 1);
    dateTimeContainer->addWidget(endTimeEdit, 1, 2);
    dateTimeContainer->setColumnStretch(1, 1);
    dateTimeContainer->setColumnStretch(2, 1);
    dateTimeContainer->setColumnStretch(3, 2);
    dateTimeContainer->setContentsMargins(0, 0, 0, 0);
    dateTimeContainer->setVerticalSpacing(3);

    fileBrowse = new FileBrowseWidget;
    fileBrowse->setToolTip(tr("<b>Load:</b> Load an existing time lag file"));
    fileBrowse->setDialogTitle(tr("Select the Time Lag Optimization File"));
    fileBrowse->setDialogWorkingDir(WidgetUtils::getSearchPathHint());
    fileBrowse->setDialogFilter(tr("All Files (*.*)"));

    auto existingFileLayout = new QHBoxLayout;
    existingFileLayout->addWidget(existingRadio);
    existingFileLayout->addWidget(fileBrowse);
    existingFileLayout->setStretch(2, 1);
    existingFileLayout->setContentsMargins(0, 0, 0, 0);
    existingFileLayout->setSpacing(0);

    radioGroup = new QButtonGroup(this);
    radioGroup->addButton(existingRadio, 0);
    radioGroup->addButton(nonExistingRadio, 1);

    h2oTitleLabel = new QLabel(tr("Water vapor time lag as a function of relative humidity"));
    h2oTitleLabel->setProperty("blueLabel", true);

    pgRangeLabel = new ClickLabel(tr("Plausibility range around median value :"));
    pgRangeLabel->setToolTip(tr("<b>Plausibility range around median value:</b> The plausibility range is defined as the median time lag, %1 <i>n</i> times the MAD (median of the absolute deviations from the median time lag). Specify <i>n</i> here. The value of 1.5 was heuristically found to be optimal.").arg(Defs::PLUSMINUS));
    pgRangeSpin = new QDoubleSpinBox;
    pgRangeSpin->setDecimals(1);
    pgRangeSpin->setRange(0.1, 100.0);
    pgRangeSpin->setSingleStep(0.1);
    pgRangeSpin->setAccelerated(true);
    pgRangeSpin->setSuffix(tr("  [mad]"));
    pgRangeSpin->setToolTip(pgRangeLabel->toolTip());
    pgRangeLabel_2 = new QLabel(tr("(<tt>%1%2n%3mad</tt>, where you set <tt>n</tt>)").arg(Defs::MICRO).arg(Defs::PLUSMINUS).arg(Defs::MID_DOT));

    rhClassLabel = new ClickLabel(tr("Number of RH classes :"));
    rhClassLabel->setToolTip(tr("<b>Number of RH classes:</b> Select the number or relative humidity classes, to assess water vapor time lag as a function of RH. The whole range or RH variation (0-100%) will be evenly divided according to the selected number of classes. For example, selecting 10 classes causes EddyPro to assess water vapor time lags for the classes 0-10%, 10-20%,..., 90-100%. Selecting 1 class, the label <b><i>Do not sort in RH classes</i></b> appears and will cause EddyPro to treat water vapor exactly like other passive gases. This option is only suitable for open path systems, or closed path systems with short and heated sampling lines."));

    rhClassSpin = new QSpinBox;
    rhClassSpin->setRange(1, 20);
    rhClassSpin->setSingleStep(1);
    rhClassSpin->setAccelerated(true);
    rhClassSpin->setSpecialValueText(tr("Do not sort in RH classes"));
    rhClassSpin->setToolTip(rhClassLabel->toolTip());

    gasTitleLabel = new QLabel(tr("Passive gases"));
    gasTitleLabel->setProperty("blueLabel", true);

    co2MinFluxLabel = new ClickLabel(tr("Minimum (absolute) %1 flux :").arg(Defs::CO2_STRING));
    co2MinFluxLabel->setToolTip(tr("<b>Minimum (absolute) %1 flux:</b> %1 time lags corresponding to fluxes smaller (in module) than this value will not be considered in the time lag optimization. Selecting high-enough fluxes assures that well developed turbulent conditions are met and the correlation function is well characterized.").arg(Defs::CO2_STRING));
    co2MinFluxSpin = new QDoubleSpinBox;
    co2MinFluxSpin->setDecimals(3);
    co2MinFluxSpin->setRange(0.0, 100.0);
    co2MinFluxSpin->setSingleStep(0.001);
    co2MinFluxSpin->setAccelerated(true);
    co2MinFluxSpin->setSuffix(tr("  [%1]").arg(Defs::UMOL_M2S_STRING));
    co2MinFluxSpin->setToolTip(co2MinFluxLabel->toolTip());

    ch4MinFluxLabel = new ClickLabel(tr("Minimum (absolute) %1 flux :").arg(Defs::CH4_STRING));
    ch4MinFluxLabel->setToolTip(tr("<b>Minimum (absolute) %1 flux:</b> %1 time lags corresponding to fluxes smaller (in module) than this value will not be considered in the time lag optimization. Selecting high-enough fluxes assures that well developed turbulent conditions are met and the correlation function is well characterized.").arg(Defs::CH4_STRING));
    ch4MinFluxSpin = new QDoubleSpinBox;
    ch4MinFluxSpin->setDecimals(3);
    ch4MinFluxSpin->setRange(0.0, 100.0);
    ch4MinFluxSpin->setSingleStep(0.001);
    ch4MinFluxSpin->setAccelerated(true);
    ch4MinFluxSpin->setSuffix(tr("  [%1]").arg(Defs::UMOL_M2S_STRING));
    ch4MinFluxSpin->setToolTip(ch4MinFluxLabel->toolTip());

    gas4MinFluxLabel = new ClickLabel(tr("Minimum (absolute) %1 gas flux :").arg(Defs::GAS4_STRING));
    gas4MinFluxLabel->setToolTip(tr("<b>Minimum (absolute) %1 gas flux:</b> %1 gas time lags corresponding to fluxes smaller (in module) than this value will not be considered in the time lag optimization. Selecting high-enough fluxes assures that well developed turbulent conditions are met and the correlation function is well characterized.").arg(Defs::GAS4_STRING));
    gas4MinFluxSpin = new QDoubleSpinBox;
    gas4MinFluxSpin->setDecimals(3);
    gas4MinFluxSpin->setRange(0.0, 100.0);
    gas4MinFluxSpin->setSingleStep(0.001);
    gas4MinFluxSpin->setAccelerated(true);
    gas4MinFluxSpin->setSuffix(tr("  [%1]").arg(Defs::UMOL_M2S_STRING));
    gas4MinFluxSpin->setToolTip(gas4MinFluxLabel->toolTip());

    leMinFluxLabel = new ClickLabel(tr("Minimum latent heat flux :"));
    leMinFluxLabel->setToolTip(tr("<b>Minimum latent heat flux:</b> Minimum latent heat flux: H<sub>2</sub>O time lags corresponding to latent heat fluxes smaller than this value will not be considered in the time lag optimization. Selecting high-enough fluxes assures that well developed turbulent conditions are met and the correlation function is well characterized."));
    leMinFluxSpin = new QDoubleSpinBox;
    leMinFluxSpin->setDecimals(1);
    leMinFluxSpin->setRange(0.0, 1000.0);
    leMinFluxSpin->setSingleStep(0.1);
    leMinFluxSpin->setAccelerated(true);
    leMinFluxSpin->setSuffix(tr("  [%1]").arg(Defs::W_M2_STRING));
    leMinFluxSpin->setToolTip(leMinFluxLabel->toolTip());

    searchWindowLabel = new QLabel(tr("Time lag searching windows"));
    searchWindowLabel->setProperty("blueLabel", true);

    minLabel = new QLabel(tr("Minimum"));
    minLabel->setProperty("blueLabel", true);
    minLabel->setToolTip(tr("<b>Minimum:</b> Minimum time lag for each gas, for initializing the time lag optimization procedure. The searching window defined by Minimum and Maximum should be large enough to accommodate all possible time lags. Leave as <i>Not set</i> if in doubt, EddyPro will initialize it automatically."));

    maxLabel = new QLabel(tr("Maximum"));
    maxLabel->setProperty("blueLabel", true);
    maxLabel->setToolTip(tr("<b>Maximum:</b> Maximum time lag for each gas, for initializing the time lag optimization procedure. The searching window defined by Minimum and Maximum should be large enough to accommodate all possible time lags. In particular, maximum time lags of water vapor in closed path systems can up to ten times higher than its nominal value, or even higher. Leave as <i>Not set</i> if in doubt, EddyPro will initialize it automatically."));

    co2Label = new ClickLabel(tr("%1 :").arg(Defs::CO2_STRING));

    minCo2TlSpin = new QDoubleSpinBox;
    minCo2TlSpin->setDecimals(1);
    minCo2TlSpin->setRange(-1000.1, 1000.0);
    minCo2TlSpin->setSingleStep(0.1);
    minCo2TlSpin->setSpecialValueText(tr("Detect automatically"));
    minCo2TlSpin->setAccelerated(true);
    minCo2TlSpin->setSuffix(tr("  [s]"));
    minCo2TlSpin->setToolTip(minLabel->toolTip());

    maxCo2TlSpin = new QDoubleSpinBox;
    maxCo2TlSpin->setDecimals(1);
    maxCo2TlSpin->setRange(-1000.1, 1000.0);
    maxCo2TlSpin->setSingleStep(0.1);
    maxCo2TlSpin->setSpecialValueText(tr("Detect automatically"));
    maxCo2TlSpin->setAccelerated(true);
    maxCo2TlSpin->setSuffix(tr("  [s]"));
    maxCo2TlSpin->setToolTip(maxLabel->toolTip());

    h2oLabel = new ClickLabel(tr("%1 :").arg(Defs::H2O_STRING));

    minH2oTlSpin = new QDoubleSpinBox;
    minH2oTlSpin->setDecimals(1);
    minH2oTlSpin->setRange(-1000.1, 1000.0);
    minH2oTlSpin->setSingleStep(0.1);
    minH2oTlSpin->setSpecialValueText(tr("Detect automatically"));
    minH2oTlSpin->setAccelerated(true);
    minH2oTlSpin->setSuffix(tr("  [s]"));
    minH2oTlSpin->setToolTip(minLabel->toolTip());

    maxH2oTlSpin = new QDoubleSpinBox;
    maxH2oTlSpin->setDecimals(1);
    maxH2oTlSpin->setRange(-1000.1, 1000.0);
    maxH2oTlSpin->setSingleStep(0.1);
    maxH2oTlSpin->setSpecialValueText(tr("Detect automatically"));
    maxH2oTlSpin->setAccelerated(true);
    maxH2oTlSpin->setSuffix(tr("  [s]"));
    maxH2oTlSpin->setToolTip(maxLabel->toolTip());

    ch4Label = new ClickLabel(tr("%1 :").arg(Defs::CH4_STRING));

    minCh4TlSpin = new QDoubleSpinBox;
    minCh4TlSpin->setDecimals(1);
    minCh4TlSpin->setRange(-1000.1, 1000.0);
    minCh4TlSpin->setSingleStep(0.1);
    minCh4TlSpin->setSpecialValueText(tr("Detect automatically"));
    minCh4TlSpin->setAccelerated(true);
    minCh4TlSpin->setSuffix(tr("  [s]"));
    minCh4TlSpin->setToolTip(minLabel->toolTip());

    maxCh4TlSpin = new QDoubleSpinBox;
    maxCh4TlSpin->setDecimals(1);
    maxCh4TlSpin->setRange(-1000.1, 1000.0);
    maxCh4TlSpin->setSingleStep(0.1);
    maxCh4TlSpin->setSpecialValueText(tr("Detect automatically"));
    maxCh4TlSpin->setAccelerated(true);
    maxCh4TlSpin->setSuffix(tr("  [s]"));
    maxCh4TlSpin->setToolTip(maxLabel->toolTip());

    gas4Label = new ClickLabel(tr("%1 gas :").arg(Defs::GAS4_STRING));

    minGas4TlSpin = new QDoubleSpinBox;
    minGas4TlSpin->setDecimals(1);
    minGas4TlSpin->setRange(-1000.1, 1000.0);
    minGas4TlSpin->setSingleStep(0.1);
    minGas4TlSpin->setSpecialValueText(tr("Detect automatically"));
    minGas4TlSpin->setAccelerated(true);
    minGas4TlSpin->setSuffix(tr("  [s]"));
    minGas4TlSpin->setToolTip(minLabel->toolTip());

    maxGas4TlSpin = new QDoubleSpinBox;
    maxGas4TlSpin->setDecimals(1);
    maxGas4TlSpin->setRange(-1000.1, 1000.0);
    maxGas4TlSpin->setSingleStep(0.1);
    maxGas4TlSpin->setSpecialValueText(tr("Detect automatically"));
    maxGas4TlSpin->setAccelerated(true);
    maxGas4TlSpin->setSuffix(tr("  [s]"));
    maxGas4TlSpin->setToolTip(maxLabel->toolTip());

    auto propertiesLayout = new QGridLayout;
    propertiesLayout->addLayout(existingFileLayout, 0, 0, 1, -1);
    propertiesLayout->addWidget(nonExistingRadio, 1, 0);
    propertiesLayout->addWidget(subsetCheckBox, 1, 1, 1, 1, Qt::AlignLeft);
    propertiesLayout->addWidget(startDateLabel, 1, 1, Qt::AlignRight);
    propertiesLayout->addLayout(dateTimeContainer, 1, 2, 2, 1);
    propertiesLayout->addWidget(endDateLabel, 2, 1, Qt::AlignRight);
    propertiesLayout->addWidget(pgRangeLabel, 3, 1, 1, 1, Qt::AlignRight);
    propertiesLayout->addWidget(pgRangeSpin, 3, 2);
    propertiesLayout->addWidget(pgRangeLabel_2, 3, 3);

    propertiesLayout->addWidget(h2oTitleLabel, 4, 0, 1, 2);

    propertiesLayout->addWidget(rhClassLabel, 5, 1, Qt::AlignRight);
    propertiesLayout->addWidget(rhClassSpin, 5, 2);
    propertiesLayout->addWidget(leMinFluxLabel, 6, 1, Qt::AlignRight);
    propertiesLayout->addWidget(leMinFluxSpin, 6, 2);

    propertiesLayout->addWidget(gasTitleLabel, 7, 0);

    propertiesLayout->addWidget(co2MinFluxLabel, 8, 1, Qt::AlignRight);
    propertiesLayout->addWidget(co2MinFluxSpin, 8, 2);
    propertiesLayout->addWidget(ch4MinFluxLabel, 9, 1, Qt::AlignRight);
    propertiesLayout->addWidget(ch4MinFluxSpin, 9, 2);
    propertiesLayout->addWidget(gas4MinFluxLabel, 10, 1, Qt::AlignRight);
    propertiesLayout->addWidget(gas4MinFluxSpin, 10, 2);

    propertiesLayout->addWidget(searchWindowLabel, 11, 0);
    propertiesLayout->addWidget(minLabel, 12, 1);
    propertiesLayout->addWidget(maxLabel, 12, 2);
    propertiesLayout->addWidget(co2Label, 13, 0, Qt::AlignRight);
    propertiesLayout->addWidget(minCo2TlSpin, 13, 1);
    propertiesLayout->addWidget(maxCo2TlSpin, 13, 2);
    propertiesLayout->addWidget(h2oLabel, 14, 0, Qt::AlignRight);
    propertiesLayout->addWidget(minH2oTlSpin, 14, 1);
    propertiesLayout->addWidget(maxH2oTlSpin, 14, 2);
    propertiesLayout->addWidget(ch4Label, 15, 0, Qt::AlignRight);
    propertiesLayout->addWidget(minCh4TlSpin, 15, 1);
    propertiesLayout->addWidget(maxCh4TlSpin, 15, 2);
    propertiesLayout->addWidget(gas4Label, 16, 0, Qt::AlignRight);
    propertiesLayout->addWidget(minGas4TlSpin, 16, 1);
    propertiesLayout->addWidget(maxGas4TlSpin, 16, 2);
    propertiesLayout->setVerticalSpacing(3);
    propertiesLayout->setRowMinimumHeight(2, 10);
    propertiesLayout->setContentsMargins(3, 3, 3, 3);

    auto propertiesFrame = new QWidget;
    propertiesFrame->setLayout(propertiesLayout);
    propertiesFrame->setMinimumWidth(propertiesFrame->sizeHint().width());

    auto okButton = WidgetUtils::createCommonButton(this, tr("Ok"));

    auto mainLayout = new QGridLayout(this);
    mainLayout->addWidget(groupTitle, 0, 0);
    mainLayout->addWidget(hrLabel, 1, 0);
    mainLayout->addWidget(propertiesFrame, 2, 0);
    mainLayout->addWidget(okButton, 3, 0, 1, 1, Qt::AlignCenter);
    mainLayout->setVerticalSpacing(10);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    connect(radioGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(updateTlMode(int)));

    connect(radioGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(radioClicked(int)));

    connect(fileBrowse, &FileBrowseWidget::pathChanged,
            this, &TimeLagSettingsDialog::updateFile);
    connect(fileBrowse, &FileBrowseWidget::pathSelected,
        this, &TimeLagSettingsDialog::testSelectedFile);

    connect(subsetCheckBox, &QCheckBox::toggled,
            this, &TimeLagSettingsDialog::updateSubsetSelection);

    connect(startDateLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onStartDateLabelClicked);
    connect(startDateEdit, &QDateEdit::dateChanged,
            this, &TimeLagSettingsDialog::updateStartDate);
    connect(startTimeEdit, &QTimeEdit::timeChanged,
            this, &TimeLagSettingsDialog::updateStartTime);

    connect(endDateLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onEndDateLabelClicked);
    connect(endDateEdit, &QDateEdit::dateChanged,
            this, &TimeLagSettingsDialog::updateEndDate);
    connect(endTimeEdit, &QTimeEdit::timeChanged,
            this, &TimeLagSettingsDialog::updateEndTime);

    connect(rhClassLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onRhClassClicked);
    connect(rhClassSpin, SIGNAL(valueChanged(int)),
            this, SLOT(updateRhClass(int)));

    connect(co2MinFluxLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onCo2MinFluxClicked);
    connect(co2MinFluxSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateCo2MinFlux(double)));

    connect(ch4MinFluxLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onCh4MinFluxClicked);
    connect(ch4MinFluxSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateCh4MinFlux(double)));

    connect(gas4MinFluxLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onGas4MinFluxClicked);
    connect(gas4MinFluxSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateGas4MinFlux(double)));

    connect(leMinFluxLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onLeMinFluxClicked);
    connect(leMinFluxSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateLeMinFlux(double)));

    connect(pgRangeLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onPgRangeLabelClicked);
    connect(pgRangeSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updatePgRange(double)));

    connect(co2Label, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onCo2LabelClicked);
    connect(minCo2TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMinCo2Tl(double)));
    connect(maxCo2TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMaxCo2Tl(double)));

    connect(h2oLabel, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onH2oLabelClicked);
    connect(minH2oTlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMinH2oTl(double)));
    connect(maxH2oTlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMaxH2oTl(double)));

    connect(ch4Label, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onCh4LabelClicked);
    connect(minCh4TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMinCh4Tl(double)));
    connect(maxCh4TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMaxCh4Tl(double)));

    connect(gas4Label, &ClickLabel::clicked,
            this, &TimeLagSettingsDialog::onGas4LabelClicked);
    connect(minGas4TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMinGas4Tl(double)));
    connect(maxGas4TlSpin, SIGNAL(valueChanged(double)),
            this, SLOT(updateMaxGas4Tl(double)));

    connect(okButton, &QPushButton::clicked,
            this, &TimeLagSettingsDialog::close);

    // init
    forceEndDatePolicy();
    forceEndTimePolicy();
}

TimeLagSettingsDialog::~TimeLagSettingsDialog()
{
    qDebug() << Q_FUNC_INFO;
}

void TimeLagSettingsDialog::close()
{
    DEBUG_FUNC_NAME
    if (isVisible())
        hide();
    emit saveRequest();
}

void TimeLagSettingsDialog::reset()
{
    DEBUG_FUNC_NAME

    updateTlMode(1);

    existingRadio->setChecked(false);
    nonExistingRadio->setChecked(true);
    fileBrowse->clear();
    subsetCheckBox->setChecked(false);

    startDateEdit->setDate(QDate::fromString(ecProject_->generalStartDate(), Qt::ISODate));
    startTimeEdit->setTime(QTime::fromString(ecProject_->generalStartTime(), QStringLiteral("hh:mm")));
    endDateEdit->setDate(QDate::fromString(ecProject_->generalEndDate(), Qt::ISODate));
    endTimeEdit->setTime(QTime::fromString(ecProject_->generalEndTime(), QStringLiteral("hh:mm")));
    forceEndDatePolicy();
    forceEndTimePolicy();
    updateSubsetSelection(false);

    pgRangeSpin->setValue(1.5);
    rhClassSpin->setValue(10);
    leMinFluxSpin->setValue(20.0);
    co2MinFluxSpin->setValue(2.0);
    ch4MinFluxSpin->setValue(0.2);
    gas4MinFluxSpin->setValue(0.02);

    minCo2TlSpin->setValue(-1000.1);
    maxCo2TlSpin->setValue(-1000.1);
    minH2oTlSpin->setValue(-1000.1);
    maxH2oTlSpin->setValue(-1000.1);
    minCh4TlSpin->setValue(-1000.1);
    maxCh4TlSpin->setValue(-1000.1);
    minGas4TlSpin->setValue(-1000.1);
    maxGas4TlSpin->setValue(-1000.1);

    radioClicked(1);
}

void TimeLagSettingsDialog::partialRefresh()
{
    DEBUG_FUNC_NAME

    // save the modified flag to prevent side effects of setting widgets
    bool oldmod = ecProject_->modified();
    ecProject_->blockSignals(true);

    subsetCheckBox->setChecked(ecProject_->timelagOptSubset());
    if (ecProject_->timelagOptSubset())
    {
        startDateEdit->setDate(QDate::fromString(ecProject_->timelagOptStartDate(), Qt::ISODate));
        startTimeEdit->setTime(QTime::fromString(ecProject_->timelagOptStartTime(), QStringLiteral("hh:mm")));
        endDateEdit->setDate(QDate::fromString(ecProject_->timelagOptEndDate(), Qt::ISODate));
        endTimeEdit->setTime(QTime::fromString(ecProject_->timelagOptEndTime(), QStringLiteral("hh:mm")));
    }
    else
    {
        startDateEdit->setDate(QDate::fromString(ecProject_->generalStartDate(), Qt::ISODate));
        startTimeEdit->setTime(QTime::fromString(ecProject_->generalStartTime(), QStringLiteral("hh:mm")));
        endDateEdit->setDate(QDate::fromString(ecProject_->generalEndDate(), Qt::ISODate));
        endTimeEdit->setTime(QTime::fromString(ecProject_->generalEndTime(), QStringLiteral("hh:mm")));
    }

    // restore modified flag
    ecProject_->setModified(oldmod);
    ecProject_->blockSignals(false);
}

void TimeLagSettingsDialog::refresh()
{
    DEBUG_FUNC_NAME

    // save the modified flag to prevent side effects of setting widgets
    bool oldmod = ecProject_->modified();
    ecProject_->blockSignals(true);

    existingRadio->setChecked(!ecProject_->timelagOptMode());
    nonExistingRadio->setChecked(ecProject_->timelagOptMode());

    fileBrowse->setPath(ecProject_->timelagOptFile());

    subsetCheckBox->setChecked(ecProject_->timelagOptSubset());
    if (ecProject_->timelagOptSubset())
    {
        startDateEdit->setDate(QDate::fromString(ecProject_->timelagOptStartDate(), Qt::ISODate));
        startTimeEdit->setTime(QTime::fromString(ecProject_->timelagOptStartTime(), QStringLiteral("hh:mm")));
        endDateEdit->setDate(QDate::fromString(ecProject_->timelagOptEndDate(), Qt::ISODate));
        endTimeEdit->setTime(QTime::fromString(ecProject_->timelagOptEndTime(), QStringLiteral("hh:mm")));
    }
    else
    {
        startDateEdit->setDate(QDate::fromString(ecProject_->generalStartDate(), Qt::ISODate));
        startTimeEdit->setTime(QTime::fromString(ecProject_->generalStartTime(), QStringLiteral("hh:mm")));
        endDateEdit->setDate(QDate::fromString(ecProject_->generalEndDate(), Qt::ISODate));
        endTimeEdit->setTime(QTime::fromString(ecProject_->generalEndTime(), QStringLiteral("hh:mm")));
    }

    rhClassSpin->setValue(ecProject_->timelagOptH2oNClass());
    co2MinFluxSpin->setValue(ecProject_->timelagOptCo2MinFlux());
    ch4MinFluxSpin->setValue(ecProject_->timelagOptCh4MinFlux());
    gas4MinFluxSpin->setValue(ecProject_->timelagOptGas4MinFlux());
    leMinFluxSpin->setValue(ecProject_->timelagOptLeMinFlux());
    pgRangeSpin->setValue(ecProject_->timelagOptPgRange());

    minCo2TlSpin->setValue(ecProject_->timelagOptCo2MinLag());
    maxCo2TlSpin->setValue(ecProject_->timelagOptCo2MaxLag());
    minH2oTlSpin->setValue(ecProject_->timelagOptH2oMinLag());
    maxH2oTlSpin->setValue(ecProject_->timelagOptH2oMaxLag());
    minCh4TlSpin->setValue(ecProject_->timelagOptCh4MinLag());
    maxCh4TlSpin->setValue(ecProject_->timelagOptCh4MaxLag());
    minGas4TlSpin->setValue(ecProject_->timelagOptGas4MinLag());
    maxGas4TlSpin->setValue(ecProject_->timelagOptGas4MaxLag());

    radioClicked(ecProject_->timelagOptMode());

    // restore modified flag
    ecProject_->setModified(oldmod);
    ecProject_->blockSignals(false);
}

void TimeLagSettingsDialog::setDateRange(QPair<QDateTime, QDateTime> dates)
{
    if (!ecProject_->timelagOptSubset())
    {
        startDateEdit->setDate(dates.first.date());
        endDateEdit->setDate(dates.second.date());
    }
}

void TimeLagSettingsDialog::updateTlMode(int radioButton)
{
    ecProject_->setTimelagOptMode(radioButton);
}

void TimeLagSettingsDialog::radioClicked(int radioButton)
{
    if (radioButton == 0)
    {
        fileBrowse->setEnabled(true);
        subsetCheckBox->setEnabled(false);
        startDateLabel->setEnabled(false);
        startDateEdit->setEnabled(false);
        lockedIcon->setEnabled(false);
        endDateLabel->setEnabled(false);
        endDateEdit->setEnabled(false);
        rhClassLabel->setEnabled(false);
        rhClassSpin->setEnabled(false);
        co2MinFluxLabel->setEnabled(false);
        co2MinFluxSpin->setEnabled(false);
        ch4MinFluxLabel->setEnabled(false);
        ch4MinFluxSpin->setEnabled(false);
        gas4MinFluxLabel->setEnabled(false);
        gas4MinFluxSpin->setEnabled(false);
        leMinFluxLabel->setEnabled(false);
        leMinFluxSpin->setEnabled(false);
        pgRangeLabel->setEnabled(false);
        pgRangeLabel_2->setEnabled(false);
        pgRangeSpin->setEnabled(false);
        co2Label->setEnabled(false);
        h2oLabel->setEnabled(false);
        ch4Label->setEnabled(false);
        gas4Label->setEnabled(false);
        minCo2TlSpin->setEnabled(false);
        maxCo2TlSpin->setEnabled(false);
        minH2oTlSpin->setEnabled(false);
        maxH2oTlSpin->setEnabled(false);
        minCh4TlSpin->setEnabled(false);
        maxCh4TlSpin->setEnabled(false);
        minGas4TlSpin->setEnabled(false);
        maxGas4TlSpin->setEnabled(false);
    }
    else
    {
        fileBrowse->setEnabled(false);
        subsetCheckBox->setEnabled(true);
        startDateLabel->setEnabled(subsetCheckBox->isChecked());
        startDateEdit->setEnabled(subsetCheckBox->isChecked());
        lockedIcon->setEnabled(subsetCheckBox->isChecked());
        endDateLabel->setEnabled(subsetCheckBox->isChecked());
        endDateEdit->setEnabled(subsetCheckBox->isChecked());
        rhClassLabel->setEnabled(true);
        rhClassSpin->setEnabled(true);
        co2MinFluxLabel->setEnabled(true);
        co2MinFluxSpin->setEnabled(true);
        ch4MinFluxLabel->setEnabled(true);
        ch4MinFluxSpin->setEnabled(true);
        gas4MinFluxLabel->setEnabled(true);
        gas4MinFluxSpin->setEnabled(true);
        leMinFluxLabel->setEnabled(true);
        leMinFluxSpin->setEnabled(true);
        pgRangeLabel->setEnabled(true);
        pgRangeLabel_2->setEnabled(true);
        pgRangeSpin->setEnabled(true);
        co2Label->setEnabled(true);
        h2oLabel->setEnabled(true);
        ch4Label->setEnabled(true);
        gas4Label->setEnabled(true);
        minCo2TlSpin->setEnabled(true);
        maxCo2TlSpin->setEnabled(true);
        minH2oTlSpin->setEnabled(true);
        maxH2oTlSpin->setEnabled(true);
        minCh4TlSpin->setEnabled(true);
        maxCh4TlSpin->setEnabled(true);
        minGas4TlSpin->setEnabled(true);
        maxGas4TlSpin->setEnabled(true);
    }
}

void TimeLagSettingsDialog::onStartDateLabelClicked()
{
    DEBUG_FUNC_NAME
    startDateEdit->setFocus();
    WidgetUtils::showCalendarOf(startDateEdit);
}

void TimeLagSettingsDialog::onEndDateLabelClicked()
{
    DEBUG_FUNC_NAME
    endDateEdit->setFocus();
    WidgetUtils::showCalendarOf(endDateEdit);
}

void TimeLagSettingsDialog::updateStartDate(const QDate &d)
{
    ecProject_->setTimelagOptStartDate(d.toString(Qt::ISODate));
    forceEndDatePolicy();
}

void TimeLagSettingsDialog::updateStartTime(const QTime& t)
{
    ecProject_->setTimelagOptStartTime(t.toString(QStringLiteral("hh:mm")));
    forceEndTimePolicy();
}

void TimeLagSettingsDialog::updateEndDate(const QDate &d)
{
    ecProject_->setTimelagOptEndDate(d.toString(Qt::ISODate));
}


void TimeLagSettingsDialog::updateEndTime(const QTime& t)
{
    ecProject_->setTimelagOptEndTime(t.toString(QStringLiteral("hh:mm")));
}

// enforce (start date&time) <= (end date&time)
void TimeLagSettingsDialog::forceEndDatePolicy()
{
    DEBUG_FUNC_NAME

    endDateEdit->setMinimumDate(startDateEdit->date());
}


// enforce (start date&time) <= (end date&time)
void TimeLagSettingsDialog::forceEndTimePolicy()
{
    DEBUG_FUNC_NAME

    qDebug() << "start - end, dates:" << startDateEdit->date() << endDateEdit->date();

    if (startDateEdit->date() == endDateEdit->date())
    {
        endTimeEdit->setMinimumTime(startTimeEdit->time());
    }
    else
    {
        endTimeEdit->clearMinimumTime();
    }
}

void TimeLagSettingsDialog::updateFile(const QString& fp)
{
    ecProject_->setTimelagOptFile(QDir::cleanPath(fp));
}

void TimeLagSettingsDialog::testSelectedFile(const QString& fp)
{
    DEBUG_FUNC_NAME

    QString paramFile = QFileDialog::getOpenFileName(this,
                        tr("Select the Timelag Optimization File"),
                        WidgetUtils::getSearchPathHint(),
                        tr("All Files (*.*)")
                        );
    if (paramFile.isEmpty()) { return; }

    QFileInfo paramFilePath(paramFile);
    QString canonicalParamFile = paramFilePath.canonicalFilePath();

    AncillaryFileTest test_dialog(AncillaryFileTest::FileType::TimeLag, this);
    test_dialog.refresh(canonicalParamFile);

    auto test_result = test_dialog.makeTest();
    qDebug() << "test_result" << test_result;

    auto dialog_result = true;

    // blocking behavior if test fails
    if (!test_result)
    {
        dialog_result = test_dialog.exec();
    }

    if (dialog_result)
    {
        fileBrowse->setPath(fp);

        auto lastPath = paramFilePath.canonicalPath();
        configState_->window.last_data_path = lastPath;
        GlobalSettings::updateLastDatapath(lastPath);
    }
    else
    {
        fileBrowse->clear();
    }
}

void TimeLagSettingsDialog::onRhClassClicked()
{
    rhClassSpin->setFocus();
    rhClassSpin->selectAll();
}

void TimeLagSettingsDialog::updateRhClass(int n)
{
    ecProject_->setTimelagOptH2oNClass(n);
}

void TimeLagSettingsDialog::onCo2MinFluxClicked()
{
    co2MinFluxSpin->setFocus();
    co2MinFluxSpin->selectAll();
}

void TimeLagSettingsDialog::updateCo2MinFlux(double d)
{
    ecProject_->setTimelagOptCo2MinFlux(d);
}

void TimeLagSettingsDialog::onCh4MinFluxClicked()
{
    ch4MinFluxSpin->setFocus();
    ch4MinFluxSpin->selectAll();
}

void TimeLagSettingsDialog::updateCh4MinFlux(double d)
{
    ecProject_->setTimelagOptCh4MinFlux(d);
}

void TimeLagSettingsDialog::onGas4MinFluxClicked()
{
    gas4MinFluxSpin->setFocus();
    gas4MinFluxSpin->selectAll();
}

void TimeLagSettingsDialog::updateGas4MinFlux(double d)
{
    ecProject_->setTimelagOptGas4MinFlux(d);
}

void TimeLagSettingsDialog::onLeMinFluxClicked()
{
    leMinFluxSpin->setFocus();
    leMinFluxSpin->selectAll();
}

void TimeLagSettingsDialog::updateLeMinFlux(double d)
{
    ecProject_->setTimelagOptLeMinFlux(d);
}

void TimeLagSettingsDialog::onPgRangeLabelClicked()
{
    pgRangeSpin->setFocus();
    pgRangeSpin->selectAll();
}

void TimeLagSettingsDialog::updatePgRange(double d)
{
    ecProject_->setTimelagOptPgRange(d);
}

void TimeLagSettingsDialog::onCo2LabelClicked()
{
    minCo2TlSpin->setFocus();
    minCo2TlSpin->selectAll();
}

void TimeLagSettingsDialog::updateMinCo2Tl(double d)
{
    ecProject_->setTimelagOptCo2MinLag(d);

    // min/max constraint
    if (d >= maxCo2TlSpin->value())
    {
        maxCo2TlSpin->setValue(d + 0.1);
    }
}

void TimeLagSettingsDialog::updateMaxCo2Tl(double d)
{
    ecProject_->setTimelagOptCo2MaxLag(d);

    // min/max constraint
    if (d <= minCo2TlSpin->value())
    {
        minCo2TlSpin->setValue(d - 0.1);
    }
}

void TimeLagSettingsDialog::onH2oLabelClicked()
{
    minH2oTlSpin->setFocus();
    minH2oTlSpin->selectAll();
}

void TimeLagSettingsDialog::updateMinH2oTl(double d)
{
    ecProject_->setTimelagOptH2oMinLag(d);

    // min/max constraint
    if (d >= maxH2oTlSpin->value())
    {
        maxH2oTlSpin->setValue(d + 0.1);
    }
}

void TimeLagSettingsDialog::updateMaxH2oTl(double d)
{
    ecProject_->setTimelagOptH2oMaxLag(d);

    // min/max constraint
    if (d <= minH2oTlSpin->value())
    {
        minH2oTlSpin->setValue(d - 0.1);
    }
}

void TimeLagSettingsDialog::onCh4LabelClicked()
{
    minCh4TlSpin->setFocus();
    minCh4TlSpin->selectAll();
}

void TimeLagSettingsDialog::updateMinCh4Tl(double d)
{
    ecProject_->setTimelagOptCh4MinLag(d);

    // min/max constraint
    if (d >= maxCh4TlSpin->value())
    {
        maxCh4TlSpin->setValue(d + 0.1);
    }
}

void TimeLagSettingsDialog::updateMaxCh4Tl(double d)
{
    ecProject_->setTimelagOptCh4MaxLag(d);

    // min/max constraint
    if (d <= minCh4TlSpin->value())
    {
        minCh4TlSpin->setValue(d - 0.1);
    }
}

void TimeLagSettingsDialog::onGas4LabelClicked()
{
    minGas4TlSpin->setFocus();
    minGas4TlSpin->selectAll();
}

void TimeLagSettingsDialog::updateMinGas4Tl(double d)
{
    ecProject_->setTimelagOptGas4MinLag(d);

    // min/max constraint
    if (d >= maxGas4TlSpin->value())
    {
        maxGas4TlSpin->setValue(d + 0.1);
    }
}

void TimeLagSettingsDialog::updateMaxGas4Tl(double d)
{
    ecProject_->setTimelagOptGas4MaxLag(d);

    // min/max constraint
    if (d <= minGas4TlSpin->value())
    {
        minGas4TlSpin->setValue(d - 0.1);
    }
}

void TimeLagSettingsDialog::updateSubsetSelection(bool b)
{
    ecProject_->setTimelagOptSubset(b);

    foreach (QWidget *w,
             QWidgetList()
                  << startDateLabel
                  << startDateEdit
                  << startTimeEdit
                  << lockedIcon
                  << endDateLabel
                  << endDateEdit
                  << endTimeEdit)
    {
        w->setEnabled(b);
    }
}

void TimeLagSettingsDialog::setSmartfluxUI()
{
    bool on = configState_->project.smartfluxMode;

    nonExistingRadio->setDisabled(on);

    // block project modified() signal
    auto oldmod = false;
    if (!on)
    {
        // save the modified flag to prevent side effects of setting widgets
        oldmod = ecProject_->modified();
        ecProject_->blockSignals(true);
    }

    if (on)
    {
        radioGroup->button(0)->click();
    }

    // restore project modified() signal
    if (!on)
    {
        // restore modified flag
        ecProject_->setModified(oldmod);
        ecProject_->blockSignals(false);
    }
}
