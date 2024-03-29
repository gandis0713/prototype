#ifndef CLISTMODEL_H
#define CLISTMODEL_H

#include <QList>
#include "ilistlistener.h"

class CListModel : public QList<QString>
{
public:
    explicit CListModel();
    virtual ~CListModel();

    virtual void append(const QString &strNew);
    virtual void removeAt(int nIndex);

    void setListListener(IListListner *pListListener);

private:
    IListListner *m_pListListener;
};

#endif // CLISTMODEL_H
