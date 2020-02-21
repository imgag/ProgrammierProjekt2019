#ifndef ANNOTATIONSERVICE_H
#define ANNOTATIONSERVICE_H

#include "vcfline.h"
#include "vcftable.h"

#include <QString>
#include <QObject>
#include <QNetworkReply>
#include <QQueue>

class AnnotationService : public QObject
{
    Q_OBJECT

private :
    // Queue of line indices (for tableObj)
    QQueue<int> queue;
    VCFtable * annoTableObj;

    int currentIndex;

public:
    AnnotationService();
    AnnotationService(VCFtable* table);

    // methods
    void makeVEPrequest(VCFline &line);
    void makeVEPrequest(QString notation);
    void pullAnnotations(VCFtable &table);
    ///void handleQueue();

    void makeSingleRequest(int row);


    // needed for inheritance of QObject to use Signals & Slots
    AnnotationService(AnnotationService& rhs) = delete;

    QQueue<int> getQueue() const;

public slots:
    void set_annotation(QNetworkReply *reply);
    void handle_queue();

signals:
    void annotation_set();
    void no_connection();
};

#endif // ANNOTATIONSERVICE_H
