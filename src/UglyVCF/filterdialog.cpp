#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "impactfilter.h"
#include "annotationservice.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < FilterDialog::LASTREGION; i++){
        ui->comboBox->addItem(regionToString((Region) i));
    }
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

/**
 * @brief FilterDialog::windowOpened resets the reset variable when the filterDialog window is opened again
 */
void FilterDialog::windowOpened(){
    this->reset = false;
}

/**
 * @brief FilterDialog::getFreq returns frequency entered by the user in the main filter window or 1 if reset
 * @return
 */
double FilterDialog::getFreq(){
    if (isReset()){
        return 1;
    }
    return ui->doubleSpinBox->value();
}

/**
 * @brief FilterDialog::getFreq returns the user-entered frequency threshold from the impact window,
 *  in the respective impact field
 * @param impact
 * @return
 */
double FilterDialog::getFreq(FilterDialog::Impact impact){
    if(filterByImpact) {
        switch (impact) {
            case HIGH:
                return this->impact->getHigh();
            case MODERATE:
                return this->impact->getModerate();
            case LOW:
                return this->impact->getLow();
            case MODIFER:
                return this->impact->getModifier();
            case LASTIMPACT:
                return this->impact->getUnknown();
            default:
                return 0;
        }
    }
    return 1;
}

/**
 * @brief FilterDialog::isFilterByImpact returns if the user wants to filter by impact
 * @return
 */
bool FilterDialog::isFilterByImpact(){
    return this->filterByImpact;
}

/**
 * @brief FilterDialog::getRegion returns the user-entered region or the first if reset
 * @return
 */
FilterDialog::Region FilterDialog::getRegion(){
    if (isReset()){
        return (Region) 0;
    }

    for (int i = 0; i < LASTREGION; i++){
        if(regionToString((Region) i) == ui->comboBox->currentText()){
            return (Region) i;
        }
    }

    qDebug() << "ERROR in filterdialog.cpp getRegion: "
                "The text chosen in ComboBox could not be converted to a filter::Region enum type!";
    return LASTREGION;
}

/**
 * @brief FilterDialog::hideUnknown returns if the user wants to hide entries with unkown frequencies
 * @return
 */
bool FilterDialog::hideUnknown(){
    if (isReset()){
        return false;
    }
    return ui->hideBox->isChecked();
}

/**
 * @brief FilterDialog::isReset returns if the user wants to reset the filter
 * @return
 */
bool FilterDialog::isReset(){
    return this->reset;
}

/**
 * @brief FilterDialog::stringToImpact static method to convert a string (e.g. "HIGH")
 * into the corresponding impact enum type. If not possible returns the nonsensical "LASTIMPACT"
 * @param str
 * @return
 */
FilterDialog::Impact FilterDialog::stringToImpact(QString str) {
    if (str == "HIGH") {
        return FilterDialog::HIGH;
    } else if (str == "MODERATE") {
        return FilterDialog::MODERATE;
    } else if (str == "LOW") {
        return FilterDialog::LOW;
    } else if (str == "MODIFIER") {
        return FilterDialog::MODIFER;
    } else {
        qDebug() << "ERROR in filterdialog.cpp function stringToImpact: "
                    "given String could not be converted into enum type: " << str;
        return FilterDialog::LASTIMPACT;
    }
}

/**
 * @brief FilterDialog::regionToString static method to convert a region enum type into the corresponding string (e.g. "afr")
 * @param region
 * @return
 */
QString FilterDialog::regionToString(FilterDialog::Region region) {
    switch (region) {
    case FilterDialog::aa:
        return "aa";
        break;
    case FilterDialog::ea:
        return "ea";
        break;
    case FilterDialog::afr:
        return "afr";
        break;
    case FilterDialog::amr:
        return "amr";
        break;
    case FilterDialog::eas:
        return "eas";
        break;
    case FilterDialog::eur:
        return "eur";
        break;
    case FilterDialog::sas:
        return "sas";
        break;
    case FilterDialog::gnomad:
        return "gnomad";
        break;
    case FilterDialog::gnomad_afr:
        return "gnomad_afr";
        break;
    case FilterDialog::gnomad_amr:
        return "gnomad_amr";
        break;
    case FilterDialog::gnomad_asj:
        return "gnomad_asj";
        break;
    case FilterDialog::gnomad_eas:
        return "gnomad_eas";
        break;
    case FilterDialog::gnomad_fin:
        return "gnomad_fin";
        break;
    case FilterDialog::gnomad_nfe:
        return "gnomad_nfe";
        break;
    case FilterDialog::gnomad_oth:
        return "gnomad_oth";
        break;
    case FilterDialog::gnomad_sas:
        return "gnomad_sas";
        break;
    default:
        return "Error";
        break;
    }
}

/**
 * @brief FilterDialog::resetFilter Lets other methods kno the filter has been reset
 */
void FilterDialog::resetFilter(){
    qDebug() << __FUNCTION__;
    this->filterByImpact = false;
    this->reset = true;
}

/**
 * @brief FilterDialog::on_resetButton_clicked calls FilterDialog::resetFilter()
 */
void FilterDialog::on_resetButton_clicked()
{
    resetFilter();
}

/**
 * @brief FilterDialog::on_severityButton_clicked opens the severity frequency dialog
 * and stores the given values in impactFreq array.
 */
void FilterDialog::on_severityButton_clicked()
{
    if (!this->impact) {
        this->impact = new impactFilter(this);
    }
    impact->openWindow(regionToString(this->getRegion()));
    if (impact->exec()) {
        this->filterByImpact = impact->isFilterByImpact();
    }
}
