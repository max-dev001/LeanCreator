/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2023 Rochus Keller (me@rochus-keller.ch) for LeanCreator
**
** This file is part of LeanCreator.
**
** $QT_BEGIN_LICENSE:LGPL21$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef HELPINDEXFILTER_H
#define HELPINDEXFILTER_H

#include <core/locator/ilocatorfilter.h>

#include <QIcon>
#include <QMutex>

namespace Help {
namespace Internal {

class HelpIndexFilter : public Core::ILocatorFilter
{
    Q_OBJECT

public:
    HelpIndexFilter();
    ~HelpIndexFilter();

    // ILocatorFilter
    void prepareSearch(const QString &entry);
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                               const QString &entry);
    void accept(Core::LocatorFilterEntry selection) const;
    void refresh(QFutureInterface<void> &future);

    Q_INVOKABLE QSet<QString> searchMatches(const QString &databaseFilePath,
                                          const QString &term, int limit);
signals:
    void linkActivated(const QUrl &link) const;
    void linksActivated(const QMap<QString, QUrl> &links, const QString &key) const;

private:
    void invalidateCache();

    QStringList m_helpDatabases;
    QSet<QString> m_keywordCache;
    QString m_searchTermCache;
    bool m_needsUpdate;
    QMutex m_mutex;
    QIcon m_icon;
};

} // namespace Internal
} // namespace Help

#endif // HELPINDEXFILTER_H
