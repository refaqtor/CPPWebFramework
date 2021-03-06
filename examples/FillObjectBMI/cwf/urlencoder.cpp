#include "urlencoder.h"

namespace CWF
{
    QString URLEncoder::decode(const QByteArray &url)
    {
        QUrl original(url);
        original.setQuery(original.query(QUrl::FullyDecoded), QUrl::DecodedMode);

        return original.toString();
    }

    QString URLEncoder::encode(const QByteArray &url)
    {
        QUrl original(url);
        return original.toEncoded();
    }

    QString URLEncoder::paramEncode(const QByteArray &param)
    {
        QUrl original("?p=" + param);
        original.setQuery(original.query(QUrl::FullyDecoded), QUrl::DecodedMode);

        return original.toString().remove(0, 3);
    }

    QString URLEncoder::paramDecode(const QByteArray &param)
    {
        QUrl original("?p=" + param);
        return original.toEncoded().remove(0, 3);
    }
}
