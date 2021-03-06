#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "annotationservice.h"
#include "vcftable.h"
#include "filterdialog.h"

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    void parseVCF(QString filename);

    Ui::MainWindow *ui;

    AnnotationService * annotationService;

    VCFtable tableObj;

    FilterDialog * filter = nullptr;

    QProcess * process;

    // pipeline parameters
    QString pipelineWD;
    QString pipelinePath;
    QString refGenPath;

    // row of the cell currently clicked on
    int cellClicked;

    // Methods
    void openAnnoService();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void handlePipelineFinished(int, QProcess::ExitStatus);

    void handle_pipeline_working();

    void on_actionVCF_file_triggered();

    void on_actionset_pipeline_triggered();

    void on_actionFastQ_file_triggered();

    void on_actionset_reference_genome_triggered();

    void on_actionpull_all_annotations_triggered();

    void on_tableWidget_cellClicked(int row, int);

    void on_actionhide_annotations_triggered();

    void on_actionFilter_by_Frequency_triggered();

    void on_actionDelete_all_annotations_triggered();

    void pop_no_connection();

    void updateAnnoWidget(int rowUpdated);

    void showAnnoProgress();

    void updateAnnoProgress();

    void update_row(int index);
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_actionDelete_current_annotation_triggered();
};
#endif // MAINWINDOW_H
