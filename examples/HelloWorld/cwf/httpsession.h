/**
  @file httpsession.h
  @author Herik Lima
*/

#ifndef HTTPSESSION_H
#define HTTPSESSION_H

#include <QMap>
#include "httpcookie.h"
#include <atomic>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QStringList>
#include <QMutexLocker>
#include "qmapthreadsafety.h"

namespace CWF
{
    /**
     * @brief The HttpSession class holds information about a client.
     */
    class HttpSession
    {
        friend class HttpReadRequest;
        QString id;
        qint64 creationTime;
        qint64 lastAccessedTime;
        qint64 sessionExpirationTime;
        bool   autoClearAttributes = false;
        bool   expired = false;
        QMapThreadSafety<QString, QObject*> attributes;
        mutable QMutex mutex;
    public:
        /**
         * @brief
         * @param id
         * @param parent
         */
        explicit HttpSession(const QString &id);
        ~HttpSession();
        /**
         * @brief getAttribute
         * @param name
         * @return
         */
        QObject *getAttribute(const QString &name) const;
        /**
         * @brief getAttributeNames
         * @return
         */
        QStringList getAttributeNames();
        /**
         * @brief getCreationTime
         * @return
         */
        qint64 getCreationTime() const;
        /**
         * @brief getId
         * @return
         */
        QString getId() const;
        /**
         * @brief getLastAccessedTime
         * @return
         */
        qint64 getLastAccessedTime() const;
        /**
         * @brief validate
         */
        void validate();
        /**
         * @brief invalidate
         */
        void invalidate();
        /**
         * @brief removeAttribute
         * @param name
         */
        void removeAttribute(const QString &name);
        /**
         * @brief This method add an attribute to the session.
         * @param name
         * @param value
         */
        void addAttribute(const QString &name, QObject *value);
        /**
         * @brief getAutoClearAttributes
         * @return bool
         */
        bool getAutoClearAttributes() const;
        /**
         * @brief setAutoClearAttributes
         * @param value
         */
        void setAutoClearAttributes(bool value);
        /**
         * @brief This method checks if the session is expired.
         * @return bool
         */
        bool isExpired();
    };
}

#endif // HTTPSESSION_H
