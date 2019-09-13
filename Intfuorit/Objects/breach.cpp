/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017-2019 Hüssenbergnetz / Matthias Fehring
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

#include "breach_p.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QLocale>
#include <QDebug>

using namespace Intfuorit;

Breach::Breach() :
    d(new BreachData)
{

}

Breach::Breach(const QString &title, const QString &name, const QString &domain, QDate breachDate, const QDateTime &addedDate, const QDateTime &modifiedDate, quint32 pwnCount, const QString &description, const QStringList &dataClasses, bool isVerified, bool isFabricated, bool isSensitive, bool isActive, bool isRetired, bool isSpamList, const QUrl &logoPath) :
    d(new BreachData(title, name, domain, breachDate, addedDate, modifiedDate, pwnCount, description, dataClasses, isVerified, isFabricated, isSensitive, isActive, isRetired, isSpamList, logoPath))
{

}

Breach::Breach(const Breach &other) :
    d(other.d)
{

}

Breach& Breach::operator=(const Breach &other)
{
    d = other.d;
    return *this;
}

Breach& Breach::operator=(Breach &&other)
{
    swap(other);
    return *this;
}

Breach::~Breach()
{

}

void Breach::swap(Breach &other)
{
    std::swap(d, other.d);
}

QString Breach::title() const { return d->title; }

QString Breach::name() const { return d->name; }

QString Breach::domain() const { return d->domain; }

QDate Breach::breachDate() const { return d->breachDate; }

QDateTime Breach::addedDate() const { return d->addedDate; }

QDateTime Breach::modifiedDate() const { return d->modifiedDate; }

quint32 Breach::pwnCount() const { return d->pwnCount; }

QString Breach::description() const { return d->description; }

QStringList Breach::dataClasses() const { return d->dataClasses; }

QStringList Breach::dataClassesTranslated() const
{
    static QHash<QString,QString> trans({
                                            //% "Account balances"
                                            {QStringLiteral("Account balances"), qtTrId("libintfuorit-account-balances")},
                                            //% "Address book contacts"
                                            {QStringLiteral("Address book contacts"), qtTrId("libintfuorit-address-book-contacts")},
                                            //% "Age groups"
                                            {QStringLiteral("Age groups"), qtTrId("libintfuorit-age-groups")},
                                            //% "Ages"
                                            {QStringLiteral("Ages"), qtTrId("libintfuorit-ages")},
                                            //% "Apps installed on devices"
                                            {QStringLiteral("Apps installed on devices"), qtTrId("libintfuorit-apps-installed-on-devices")},
                                            //% "Astrological signs"
                                            {QStringLiteral("Astrological signs"), qtTrId("libintfuorit-astrological-signs")},
                                            //% "Audio recordings"
                                            {QStringLiteral("Audio recordings"), qtTrId("libintfuorit-audio-recordings")},
                                            //% "Auth tokens"
                                            {QStringLiteral("Auth tokens"), qtTrId("libintfuorit-auth-tokens")},
                                            //% "Avatars"
                                            {QStringLiteral("Avatars"), qtTrId("libintfuorit-avatars")},
                                            //% "Bank account numbers"
                                            {QStringLiteral("Bank account numbers"), qtTrId("libintfuorit-bank-account-numbers")},
                                            //% "Beauty ratings"
                                            {QStringLiteral("Beauty ratings"), qtTrId("libintfuorit-beauty-ratings")},
                                            //% "Biometric data"
                                            {QStringLiteral("Biometric data"), qtTrId("libintfuorit-biometric-data")},
                                            //% "Bios"
                                            {QStringLiteral("Bios"), qtTrId("libintfuorit-bios")},
                                            //% "Browser user agent details"
                                            {QStringLiteral("Browser user agent details"), qtTrId("libintfuorit-browser-user-agent-details")},
                                            //% "Browsing histories"
                                            {QStringLiteral("Browsing histories"), qtTrId("libintfuorit-browsing-histories")},
                                            //% "Buying preferences"
                                            {QStringLiteral("Buying preferences"), qtTrId("libintfuorit-buying-preferences")},
                                            //% "Car ownership statuses"
                                            {QStringLiteral("Car ownership statuses"), qtTrId("libintfuorit-car-ownership-statuses")},
                                            //% "Career levels"
                                            {QStringLiteral("Career levels"), qtTrId("libintfuorit-career-levels")},
                                            //% "Cellular network names"
                                            {QStringLiteral("Cellular network names"), qtTrId("libintfuorit-cellular-network-names")},
                                            //% "Charitable donations"
                                            {QStringLiteral("Charitable donations"), qtTrId("libintfuorit-charitable-donations")},
                                            //% "Chat logs"
                                            {QStringLiteral("Chat logs"), qtTrId("libintfuorit-chat-logs")},
                                            //% "Credit card CVV"
                                            {QStringLiteral("Credit card CVV"), qtTrId("libintfuorit-credit-card-cvv")},
                                            //% "Credit cards"
                                            {QStringLiteral("Credit cards"), qtTrId("libintfuorit-credit-cards")},
                                            //% "Credit status information"
                                            {QStringLiteral("Credit status information"), qtTrId("libintfuorit-credit-status-information")},
                                            //% "Customer feedback"
                                            {QStringLiteral("Customer feedback"), qtTrId("libintfuorit-customer-feedback")},
                                            //% "Customer interactions"
                                            {QStringLiteral("Customer interactions"), qtTrId("libintfuorit-customer-interactions")},
                                            //% "Dates of birth"
                                            {QStringLiteral("Dates of birth"), qtTrId("libintfuorit-dates-of-birth")},
                                            //% "Deceased date"
                                            {QStringLiteral("Deceased date"), qtTrId("libintfuorit-deceased-date")},
                                            //% "Deceased statuses"
                                            {QStringLiteral("Deceased statuses"), qtTrId("libintfuorit-deceased-statuses")},
                                            //% "Device information"
                                            {QStringLiteral("Device information"), qtTrId("libintfuorit-device-information")},
                                            //% "Device usage tracking data"
                                            {QStringLiteral("Device usage tracking data"), qtTrId("libintfuorit-device-usage-tracking-data")},
                                            //% "Drinking habits"
                                            {QStringLiteral("Drinking habits"), qtTrId("libintfuorit-drinking-habits")},
                                            //% "Drug habits"
                                            {QStringLiteral("Drug habits"), qtTrId("libintfuorit-drug-habits")},
                                            //% "Eating habits"
                                            {QStringLiteral("Eating habits"), qtTrId("libintfuorit-eating-habits")},
                                            //% "Education levels"
                                            {QStringLiteral("Education levels"), qtTrId("libintfuorit-education-levels")},
                                            //% "Email addresses"
                                            {QStringLiteral("Email addresses"), qtTrId("libintfuorit-email-addresses")},
                                            //% "Email messages"
                                            {QStringLiteral("Email messages"), qtTrId("libintfuorit-email-messages")},
                                            //% "Employers"
                                            {QStringLiteral("Employers"), qtTrId("libintfuorit-employers")},
                                            //% "Employment statuses"
                                            {QStringLiteral("Employment statuses"), qtTrId("libintfuorit-employment-statuses")},
                                            //% "Ethnicities"
                                            {QStringLiteral("Ethnicities"), qtTrId("libintfuorit-ethnicities")},
                                            //% "Family members' names"
                                            {QStringLiteral("Family members' names"), qtTrId("libintfuorit-family-members'-names")},
                                            //% "Family plans"
                                            {QStringLiteral("Family plans"), qtTrId("libintfuorit-family-plans")},
                                            //% "Family structure"
                                            {QStringLiteral("Family structure"), qtTrId("libintfuorit-family-structure")},
                                            //% "Financial investments"
                                            {QStringLiteral("Financial investments"), qtTrId("libintfuorit-financial-investments")},
                                            //% "Financial transactions"
                                            {QStringLiteral("Financial transactions"), qtTrId("libintfuorit-financial-transactions")},
                                            //% "Fitness levels"
                                            {QStringLiteral("Fitness levels"), qtTrId("libintfuorit-fitness-levels")},
                                            //% "Genders"
                                            {QStringLiteral("Genders"), qtTrId("libintfuorit-genders")},
                                            //% "Geographic locations"
                                            {QStringLiteral("Geographic locations"), qtTrId("libintfuorit-geographic-locations")},
                                            //% "Government issued IDs"
                                            {QStringLiteral("Government issued IDs"), qtTrId("libintfuorit-government-issued-ids")},
                                            //% "Health insurance information"
                                            {QStringLiteral("Health insurance information"), qtTrId("libintfuorit-health-insurance-information")},
                                            //% "Historical passwords"
                                            {QStringLiteral("Historical passwords"), qtTrId("libintfuorit-historical-passwords")},
                                            //% "Home loan information"
                                            {QStringLiteral("Home loan information"), qtTrId("libintfuorit-home-loan-information")},
                                            //% "Home ownership statuses"
                                            {QStringLiteral("Home ownership statuses"), qtTrId("libintfuorit-home-ownership-statuses")},
                                            //% "Homepage URLs"
                                            {QStringLiteral("Homepage URLs"), qtTrId("libintfuorit-homepage-urls")},
                                            //% "IMEI numbers"
                                            {QStringLiteral("IMEI numbers"), qtTrId("libintfuorit-imei-numbers")},
                                            //% "IMSI numbers"
                                            {QStringLiteral("IMSI numbers"), qtTrId("libintfuorit-imsi-numbers")},
                                            //% "Income levels"
                                            {QStringLiteral("Income levels"), qtTrId("libintfuorit-income-levels")},
                                            //% "Instant messenger identities"
                                            {QStringLiteral("Instant messenger identities"), qtTrId("libintfuorit-instant-messenger-identities")},
                                            //% "IP addresses"
                                            {QStringLiteral("IP addresses"), qtTrId("libintfuorit-ip-addresses")},
                                            //% "Job titles"
                                            {QStringLiteral("Job titles"), qtTrId("libintfuorit-job-titles")},
                                            //% "MAC addresses"
                                            {QStringLiteral("MAC addresses"), qtTrId("libintfuorit-mac-addresses")},
                                            //% "Marital statuses"
                                            {QStringLiteral("Marital statuses"), qtTrId("libintfuorit-marital-statuses")},
                                            //% "Names"
                                            {QStringLiteral("Names"), qtTrId("libintfuorit-names")},
                                            //% "Nationalities"
                                            {QStringLiteral("Nationalities"), qtTrId("libintfuorit-nationalities")},
                                            //% "Net worths"
                                            {QStringLiteral("Net worths"), qtTrId("libintfuorit-net-worths")},
                                            //% "Nicknames"
                                            {QStringLiteral("Nicknames"), qtTrId("libintfuorit-nicknames")},
                                            //% "Occupations"
                                            {QStringLiteral("Occupations"), qtTrId("libintfuorit-occupations")},
                                            //% "Parenting plans"
                                            {QStringLiteral("Parenting plans"), qtTrId("libintfuorit-parenting-plans")},
                                            //% "Partial credit card data"
                                            {QStringLiteral("Partial credit card data"), qtTrId("libintfuorit-partial-credit-card-data")},
                                            //% "Passport numbers"
                                            {QStringLiteral("Passport numbers"), qtTrId("libintfuorit-passport-numbers")},
                                            //% "Password hints"
                                            {QStringLiteral("Password hints"), qtTrId("libintfuorit-password-hints")},
                                            //% "Passwords"
                                            {QStringLiteral("Passwords"), qtTrId("libintfuorit-passwords")},
                                            //% "Payment histories"
                                            {QStringLiteral("Payment histories"), qtTrId("libintfuorit-payment-histories")},
                                            //% "Payment methods"
                                            {QStringLiteral("Payment methods"), qtTrId("libintfuorit-payment-methods")},
                                            //% "Personal descriptions"
                                            {QStringLiteral("Personal descriptions"), qtTrId("libintfuorit-personal-descriptions")},
                                            //% "Personal health data"
                                            {QStringLiteral("Personal health data"), qtTrId("libintfuorit-personal-health-data")},
                                            //% "Personal interests"
                                            {QStringLiteral("Personal interests"), qtTrId("libintfuorit-personal-interests")},
                                            //% "Phone numbers"
                                            {QStringLiteral("Phone numbers"), qtTrId("libintfuorit-phone-numbers")},
                                            //% "Photos"
                                            {QStringLiteral("Photos"), qtTrId("libintfuorit-photos")},
                                            //% "Physical addresses"
                                            {QStringLiteral("Physical addresses"), qtTrId("libintfuorit-physical-addresses")},
                                            //% "Physical attributes"
                                            {QStringLiteral("Physical attributes"), qtTrId("libintfuorit-physical-attributes")},
                                            //% "PINs"
                                            {QStringLiteral("PINs"), qtTrId("libintfuorit-pins")},
                                            //% "Political donations"
                                            {QStringLiteral("Political donations"), qtTrId("libintfuorit-political-donations")},
                                            //% "Political views"
                                            {QStringLiteral("Political views"), qtTrId("libintfuorit-political-views")},
                                            //% "Private messages"
                                            {QStringLiteral("Private messages"), qtTrId("libintfuorit-private-messages")},
                                            //% "Professional skills"
                                            {QStringLiteral("Professional skills"), qtTrId("libintfuorit-professional-skills")},
                                            //% "Profile photos"
                                            {QStringLiteral("Profile photos"), qtTrId("libintfuorit-profile-photos")},
                                            //% "Purchases"
                                            {QStringLiteral("Purchases"), qtTrId("libintfuorit-purchases")},
                                            //% "Purchasing habits"
                                            {QStringLiteral("Purchasing habits"), qtTrId("libintfuorit-purchasing-habits")},
                                            //% "Races"
                                            {QStringLiteral("Races"), qtTrId("libintfuorit-races")},
                                            //% "Recovery email addresses"
                                            {QStringLiteral("Recovery email addresses"), qtTrId("libintfuorit-recovery-email-addresses")},
                                            //% "Relationship statuses"
                                            {QStringLiteral("Relationship statuses"), qtTrId("libintfuorit-relationship-statuses")},
                                            //% "Religions"
                                            {QStringLiteral("Religions"), qtTrId("libintfuorit-religions")},
                                            //% "Reward program balances"
                                            {QStringLiteral("Reward program balances"), qtTrId("libintfuorit-reward-program-balances")},
                                            //% "Salutations"
                                            {QStringLiteral("Salutations"), qtTrId("libintfuorit-salutations")},
                                            //% "School grades (class levels)"
                                            {QStringLiteral("School grades (class levels)"), qtTrId("libintfuorit-school-grades-(class-levels)")},
                                            //% "Security questions and answers"
                                            {QStringLiteral("Security questions and answers"), qtTrId("libintfuorit-security-questions-and-answers")},
                                            //% "Sexual fetishes"
                                            {QStringLiteral("Sexual fetishes"), qtTrId("libintfuorit-sexual-fetishes")},
                                            //% "Sexual orientations"
                                            {QStringLiteral("Sexual orientations"), qtTrId("libintfuorit-sexual-orientations")},
                                            //% "Smoking habits"
                                            {QStringLiteral("Smoking habits"), qtTrId("libintfuorit-smoking-habits")},
                                            //% "SMS messages"
                                            {QStringLiteral("SMS messages"), qtTrId("libintfuorit-sms-messages")},
                                            //% "Social connections"
                                            {QStringLiteral("Social connections"), qtTrId("libintfuorit-social-connections")},
                                            //% "Social media profiles"
                                            {QStringLiteral("Social media profiles"), qtTrId("libintfuorit-social-media-profiles")},
                                            //% "Social security numbers"
                                            {QStringLiteral("Social security numbers"), qtTrId("libintfuorit-social-security-numbers")},
                                            //% "Spoken languages"
                                            {QStringLiteral("Spoken languages"), qtTrId("libintfuorit-spoken-languages")},
                                            //% "Support tickets"
                                            {QStringLiteral("Support tickets"), qtTrId("libintfuorit-support-tickets")},
                                            //% "Survey results"
                                            {QStringLiteral("Survey results"), qtTrId("libintfuorit-survey-results")},
                                            //% "Taxation records"
                                            {QStringLiteral("Taxation records"), qtTrId("libintfuorit-taxation-records")},
                                            //% "Time zones"
                                            {QStringLiteral("Time zones"), qtTrId("libintfuorit-time-zones")},
                                            //% "Travel habits"
                                            {QStringLiteral("Travel habits"), qtTrId("libintfuorit-travel-habits")},
                                            //% "User statuses"
                                            {QStringLiteral("User statuses"), qtTrId("libintfuorit-user-statuses")},
                                            //% "User website URLs"
                                            {QStringLiteral("User website URLs"), qtTrId("libintfuorit-user-website-urls")},
                                            //% "Usernames"
                                            {QStringLiteral("Usernames"), qtTrId("libintfuorit-usernames")},
                                            //% "Utility bills"
                                            {QStringLiteral("Utility bills"), qtTrId("libintfuorit-utility-bills")},
                                            //% "Vehicle details"
                                            {QStringLiteral("Vehicle details"), qtTrId("libintfuorit-vehicle-details")},
                                            //% "Website activity"
                                            {QStringLiteral("Website activity"), qtTrId("libintfuorit-website-activity")},
                                            //% "Work habits"
                                            {QStringLiteral("Work habits"), qtTrId("libintfuorit-work-habits")},
                                            //% "Years of birth"
                                            {QStringLiteral("Years of birth"), qtTrId("libintfuorit-years-of-birth")},
                                            //% "Years of professional experience"
                                            {QStringLiteral("Years of professional experience"), qtTrId("libintfuorit-years-of-professional-experience")}
                                        });
    const QStringList dcs = d->dataClasses;
    QStringList transDcs;
    transDcs.reserve(dcs.size());
    for (const QString &dc : dcs) {
        transDcs.push_back(trans.value(dc, dc));
    }
    return transDcs;
}

QString Breach::dataClassesTranslatedString() const
{
    QLocale l;
    return l.createSeparatedList(dataClassesTranslated());
}

bool Breach::isVerified() const { return d->isVerified; }

bool Breach::isFabricated() const { return d->isFabricated; }

bool Breach::isSensitive() const { return d->isSensitive; }

bool Breach::isActive() const { return d->isActive; }

bool Breach::isRetired() const { return d->isRetired; }

bool Breach::isSpamList() const { return d->isSpamList; }

QUrl Breach::logoPath() const { return d->logoPath; }

bool Breach::operator==(const Breach &other) const
{
    return d->name == other.name();
}

bool Breach::operator!=(const Breach &other) const
{
    return d->name != other.name();
}

Breach Breach::fromJson(const QJsonObject &o)
{
    if (o.isEmpty()) {
        return Breach();
    }

    const QJsonArray dataClassesArray = o.value(QStringLiteral("DataClasses")).toArray();
    QStringList dataClasses;
    dataClasses.reserve(dataClassesArray.size());
    for (const QJsonValue &dc : dataClassesArray) {
        dataClasses << dc.toString();
    }

    return {
        o.value(QStringLiteral("Title")).toString(),
        o.value(QStringLiteral("Name")).toString(),
        o.value(QStringLiteral("Domain")).toString(),
        QDate::fromString(o.value(QStringLiteral("BreachDate")).toString(), Qt::ISODate),
        QDateTime::fromString(o.value(QStringLiteral("AddedDate")).toString(), Qt::ISODate),
        QDateTime::fromString(o.value(QStringLiteral("ModifiedDate")).toString(), Qt::ISODate),
        static_cast<quint32>(o.value(QStringLiteral("PwnCount")).toDouble()),
        o.value(QStringLiteral("Description")).toString(),
        dataClasses,
        o.value(QStringLiteral("IsVerified")).toBool(),
        o.value(QStringLiteral("IsFabricated")).toBool(),
        o.value(QStringLiteral("IsSensitive")).toBool(),
        o.value(QStringLiteral("IsActive")).toBool(),
        o.value(QStringLiteral("IsRetired")).toBool(),
        o.value(QStringLiteral("IsSpamList")).toBool(),
        QUrl(o.value(QStringLiteral("LogoPath")).toString())
    };
}

QDebug operator<<(QDebug dbg, const Intfuorit::Breach &breach)
{
    QDebugStateSaver saver(dbg);
    Q_UNUSED(saver);
    dbg.nospace() << "Intfuorit::Breach(";
    dbg << "Title: " << breach.title();
    dbg << ", Name: " << breach.name();
    dbg << ", Domain: " << breach.domain();
    dbg << ", BreachDate: " << breach.breachDate();
    dbg << ", AddedDate: " << breach.addedDate();
    dbg << ", ModifiedDate: " << breach.modifiedDate();
    dbg << ", PwnCount: " << breach.pwnCount();
    dbg << ", IsVerified: " << breach.isVerified();
    dbg << ", IsFabricated: " << breach.isFabricated();
    dbg << ", IsSensitive: " << breach.isSensitive();
    dbg << ", IsActive: " << breach.isActive();
    dbg << ", IsRetired: " << breach.isRetired();
    dbg << ", IsSpamList: " << breach.isSpamList();
    dbg << ')';
    return dbg.maybeSpace();
}

#include "moc_breach.cpp"
