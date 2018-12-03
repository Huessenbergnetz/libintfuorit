/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017 Hüssenbergnetz / Matthias Fehring
 * https://github.com/Huessenbergnetz/libintfuorit
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "error_p.h"
#include <QNetworkReply>
#include <QJsonParseError>

using namespace Intfuorit;

Error::Error() : d(new ErrorData)
{

}

Error::Error(Type type, Severity severity, const QString &text) :
    d(new ErrorData(type, severity, text))
{
    d->printOut();
}

Error::Error(QNetworkReply *reply) : d(new ErrorData)
{
    if (reply && reply->error() != QNetworkReply::NoError) {

        d->type = RequestError;
        d->severity = Critical;

        switch(reply->error()) {
        case QNetworkReply::ConnectionRefusedError:
            //% "The remote server at %1 refused the connection. (Code N1)"
            d->text = qtTrId("libintfuorit-err-net-reply-1").arg(reply->request().url().host());
            break;
        case QNetworkReply::RemoteHostClosedError:
            //% "The remote server at %1 closed the connection prematurely, before the entire reply was received and processed. (Code N2)"
            d->text = qtTrId("libintfuorit-err-net-reply-2").arg(reply->request().url().host());
            break;
        case QNetworkReply::HostNotFoundError:
            //% "The remote host name %1 was not found. (Code N3)"
            d->text = qtTrId("libintfuorit-err-net-reply-3").arg(reply->request().url().host());
            break;
        case QNetworkReply::TimeoutError:
            //% "The connection to the server at %1 timed out. (Code N4)"
            d->text = qtTrId("libintfuorit-err-net-reply-4").arg(reply->request().url().host());
            break;
        case QNetworkReply::OperationCanceledError:
            //% "The operation was canceled before it was finished. (Code N5)"
            d->text = qtTrId("libintfuorit-err-net-reply-5");
            break;
        case QNetworkReply::SslHandshakeFailedError:
            //% "The SSL/TLS handshake failed and the encrypted channel could not be established. (Code N6)"
            d->text = qtTrId("libintfuorit-err-net-reply-6");
            break;
        case QNetworkReply::TemporaryNetworkFailureError:
            //% "The connection was broken due to disconnection from the network. (Code N7)"
            d->text = qtTrId("libintfuorit-err-net-reply-7");
            break;
        case QNetworkReply::NetworkSessionFailedError:
            //% "The connection was broken due to disconnection from the network or failure to start the network. (Code N8)"
            d->text = qtTrId("libintfuorit-err-net-reply-8");
            break;
        case QNetworkReply::BackgroundRequestNotAllowedError:
            //% "The background request is not currently allowed due to platform policy. (Code N9)"
            d->text = qtTrId("libintfuorit-err-net-reply-9");
            break;
        case QNetworkReply::TooManyRedirectsError:
            //% "While following redirects, the maximum limit was reached. (Code N10)"
            d->text = qtTrId("libintfuorit-err-net-reply-10");
            break;
        case QNetworkReply::InsecureRedirectError:
            //% "While following redirects, the network access API detected a redirect from an encrypted protocol (https) to an unencrypted one (http). (Code N11)"
            d->text = qtTrId("libintfuorit-err-net-reply-11");
            break;
        case QNetworkReply::ProxyConnectionRefusedError:
            //% "The connection to the proxy server was refused (the proxy server is not accepting requests). (Code N101)"
            d->text = qtTrId("libintfuorit-err-net-reply-101");
            break;
        case QNetworkReply::ProxyConnectionClosedError:
            //% "The proxy server closed the connection prematurely, before the entire reply was received and processed. (Code N102)"
            d->text = qtTrId("libintfuorit-err-net-reply-102");
            break;
        case QNetworkReply::ProxyNotFoundError:
            //% "The proxy host name was not found (invalid proxy hostname). (Code N103)"
            d->text = qtTrId("libintfuorit-err-net-reply-103");
            break;
        case QNetworkReply::ProxyTimeoutError:
            //% "The connection to the proxy timed out or the proxy did not reply in time to the request sent. (Code N104)"
            d->text = qtTrId("libintfuorit-err-net-reply-104");
            break;
        case QNetworkReply::ProxyAuthenticationRequiredError:
            //% "The proxy requires authentication in order to honour the request but did not accept any credentials offered (if any). (Code N105)"
            d->text = qtTrId("libintfuorit-err-net-reply-105");
            break;
        case QNetworkReply::ContentAccessDenied:
            //% "The access to the remote content was denied. (Code N201)"
            d->text = qtTrId("libintfuorit-err-net-reply-201");
            break;
        case QNetworkReply::ContentOperationNotPermittedError:
            //% "The operation requested on the remote content is not permitted. (Code N202)"
            d->text = qtTrId("libintfuorit-err-net-reply-202");
            break;
        case QNetworkReply::ContentNotFoundError:
            //% "The remote content was not found at the server. (Code N203)"
            d->text = qtTrId("libintfuorit-err-net-reply-203");
            break;
        case QNetworkReply::AuthenticationRequiredError:
            //% "The remote server requires authentication to serve the content but the credentials provided were not accepted (if any). (Code N204)"
            d->text = qtTrId("libintfuorit-err-net-reply-204");
            break;
        case QNetworkReply::ContentReSendError:
            //% "The request needed to be sent again, but this failed for example because the upload data could not be read a second time. (Code N205)"
            d->text = qtTrId("libintfuorit-err-net-reply-205");
            break;
        case QNetworkReply::ContentConflictError:
            //% "The request could not be completed due to a conflict with the current state of the resource. (Code N206)"
            d->text = qtTrId("libintfuorit-err-net-reply-206");
            break;
        case QNetworkReply::ContentGoneError:
            //% "The requested resource is no longer available at the server. (Code N207)"
            d->text = qtTrId("libintfuorit-err-net-reply-207");
            break;
        case QNetworkReply::InternalServerError:
            //% "The server encountered an unexpected condition which prevented it from fulfilling the request. (Code N401)"
            d->text = qtTrId("libintfuorit-err-net-reply-401");
            break;
        case QNetworkReply::OperationNotImplementedError:
            //% "The server does not support the functionality required to fulfill the request. (Code N402)"
            d->text = qtTrId("libintfuorit-err-net-reply-402");
            break;
        case QNetworkReply::ServiceUnavailableError:
            //% "The server is unable to handle the request at this time. (Code N403)"
            d->text = qtTrId("libintfuorit-err-net-reply-403");
            break;
        case QNetworkReply::ProtocolUnknownError:
            //% "The Network Access API cannot honor the request because the protocol is not known. (Code N301)"
            d->text = qtTrId("libintfuorit-err-net-reply-301");
            break;
        case QNetworkReply::ProtocolInvalidOperationError:
            //% "The requested operation is invalid for this protocol. (Code N302)"
            d->text = qtTrId("libintfuorit-err-net-reply-302");
            break;
        case QNetworkReply::UnknownNetworkError:
            //% "An unknown network-related error was detected. (Code N99)"
            d->text = qtTrId("libintfuorit-err-net-reply-99");
            break;
        case QNetworkReply::UnknownProxyError:
            //% "An unknown proxy-related error was detected. (Code N199)"
            d->text = qtTrId("libintfuorit-err-net-reply-199");
            break;
        case QNetworkReply::UnknownContentError:
            //% "An unknown error related to the remote content was detected. (Code N299)"
            d->text = qtTrId("libintfuorit-err-net-reply-299");
            break;
        case QNetworkReply::ProtocolFailure:
            //% "A breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.). (Code N399)"
            d->text = qtTrId("libintfuorit-err-net-reply-399");
            break;
        case QNetworkReply::UnknownServerError:
            //% "An unknown error related to the server response was detected. (Code N499)"
            d->text = qtTrId("libintfuorit-err-net-reply-499");
            break;
        default:
            //% "An unknown error related to the server response was detected. (Code N499)"
            d->text = qtTrId("libintfuorit-err-net-reply-499");
            break;
        }

        d->printOut();
    }
}


Error::Error(const QJsonParseError jsonError) :
    d(new ErrorData)
{
    if (jsonError.error != QJsonParseError::NoError) {
        d->type = JSONParsingError;
        d->severity = Critical;
        d->text = jsonError.errorString();
        d->text = QStringLiteral("%1 Code(J%2)").arg(jsonError.errorString(), QString::number(jsonError.error));
    }

    d->printOut();
}


Error::Error(const Error &other) :
    d(other.d)
{

}


//Error::Error(Error &&error) noexcept :
//    d(std::move(other.d))
//{

//}


Error& Error::operator=(const Error &other)
{
    d = other.d;
    return *this;
}


Error& Error::operator=(Error &&other) noexcept
{
    swap(other);
    return *this;
}


Error::~Error()
{

}


void Error::swap(Error &other) noexcept
{
    std::swap(d, other.d);
}


Error::Type Error::type() const { return d->type; }


Error::Severity Error::severity() const { return d->severity; }


QString Error::text() const { return d->text; }


bool Error::operator!=(const Error &other) const
{
    return ((d->type != other.type()) || (d->severity != other.severity()) || (d->text != other.text()));
}


bool Error::operator==(const Error &other) const
{
    return ((d->type == other.type()) && (d->severity == other.severity()) && (d->text == other.text()));
}

#include "moc_error.cpp"
