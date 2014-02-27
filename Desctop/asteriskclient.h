#ifndef ASTERISKCLIENT_H
#define ASTERISKCLIENT_H

#include <QObject>
#include <QDateTime>

class AsteriskClient : public QObject
{
    Q_OBJECT

public:
    /*!
       * \brief The ResultCodes enum
       * Содержит коды стаусов отправки запросов на сервер
       */
      enum ResultCodes {
          CommandAccepted = 0,
          TimeoutError,
          HostNotFoundError,
          ConnectionRefusedError,
          AuthenticationError,
          WrongRequestError,
          InternalServerError,
          UnknowError
      };
      /*!
      * \brief The NotifyStatuses enum
      * Содержит статусы оповещения
      */
      enum NotifyStatuses {
      // Подготовлен к оповещению
      PreparedToNotify = 0,
      // Оповещение отменено
      CanceledNotify,
      // Оповещение отложено
      DelayedNotify,
      // Оповещение подготовлено у отправке на сервер
      PreparedToSendingToServer,
      // Оповещение успешно послано на сервер
      SendedToServer,
      // Оповещение в процессе
      NotifyInProcess,
      // Оповещение прошло успешно (на том конце ответили на вызов)
      Completed,
      // Оповещение провалено (не удалось дозвониться до абонента)
      Failed,
      // Оповещение подтверждено (абонент подтвердил прослушивание
      // оповещения путём нажатия кнопки на цифровой клавиатуре
      // телефона в тональном режиме)
      Confirmed,
      // Оповещение провалено из-за проблем со связью с сервером
      NetworkError,
      // Оповещение провалено из-за сервероной ошибки или из-за поблем с
      //авторизацией
      ServerError
      };

public:
    explicit AsteriskClient(QObject *parent = 0);
      /*!
      * \brief setPassword
      * Устанавливает пароль для REST-сессии
      * \param password
      */
      void setPassword(const QString &password);
      /*!
      * \brief setUserName
      * Устанавливает имя пользователя для REST-сессии
      * \param userName
      */
      void setUserName(const QString &userName);
      /*!
      * \brief setServiceAddress
      * Устанавливает адрес REST-сервера
      * \param address
      */
      void setServiceAddress(const QString &address);
      /*!
      * \brief setSerivcePort
      * Устанавливает сетевой порт для REST-сервера
      * \param port
      */
      void setSerivcePort(const int port);
      /*!
      * \brief setDelayBeetwenRequestNotifyStatus
      * Устанавливает задержку в милисекундах для запроса состояния
      * оповещения
      * \param delayInMs
      */
      void setDelayBeetwenRequestNotifyStatus(const int delayInMs);
      /*!
      * \brief setDelayBeetwenAttempts
      * Устанавливает задержку в секундах между попытками дозвона до
      * абонента
      * \param delay
      */
      void setDelayBeetwenAttempts(const int delay);
      /*!
      * \brief setWaitTime
      * Устанавливает время ожидания ответа абонента на вызов в секундах
      * \param waitTime
      */
      void setWaitTime(int waitTime);
      /*!
      * \brief setMaxRetries
      * Устанавливает максимальное количество попыток
      * дозвона до абонента
      * \param maxRetries
      */
      void setMaxRetries(int maxRetries);
      /*!
      * \brief createPredefinedNotify
      * Создание запроса на оповещение заранее записаным
      * сообщением.
      * \param context
      * Контекст оповещения (см. extension.conf)
      * \param extension
      * Расширение оповещения (см. extension.conf)
      * \param requestId
      * Уникальный идентификатор запроса
      */
      void createPredefinedNotify(const QString &context,
      const QString &extension,
      const QString &requestId);
      /*!
      * \brief createCustomNotify
      * Создание оповещения с произвольным контекстом
      * \param filePath
      * Путь до медиа файла
      * \param requestId
      * Уникальный идентификатор запроса
      */
      void createCustomNotify(const QString &filePath,
      const QString &requestId);
      /*!
      * \brief cancelNotify
      * Создание запроса на отмену оповещения
      * \param requestId
      * Уникальный идентификатор запроса
      */
      void cancelNotify(const QString &requestId);
      /*!
      * \brief addPhoneToNotify
      * Добавление телефонного номера для оповещения или
      * добавления идентификатора оповещения для отмены оповещения.
      * \param requestId
      * Идентификатор запроса, к которому следует добавить телефонный номер
      * для оповещения или идентификатор
      * \param phoneNumber
      * Телефонный номер для оповещения
      * \param notifyId
      * Идентификатор оповещения. При добавлении в запрос создания оповещения
      * идентифицирует именно этот телефонный номер и именно этот контет
      * оповещения, на который ссылается параметр requestId.
      * При добавлении в запрос отмены оповещения указывает идентификатор
      * оповещения, который следует отменить.
      * \return
      * true если получилось добавить телефонный номер и
      * идентификатор оповещения в запрос, иначе - false
      */
      bool addPhoneToNotify(const QString &requestId,
      const QString &phoneNumber,
      const QString &notifyId);
      /*!
      * \brief sendRequest
      * Посылает подготовленный запрос на сервер
      * \param requestId
      * Идентификатор подготовленного запроса
      * \return
      * true - подготовленный запрос с таким идентификатором существует,
      * начата отправка запроса на сервер, иначе - false
      */
      bool sendRequest(const QString &requestId);
      Q_SIGNALS:
      /*!
      * \brief finished
      * Сигнал испускается при завершении запроса на сервер
      * \param requestId
      * Идентификатор завершённого (отправенного) запроса
      * \param resultCode
      * Результат запроса (см. enum ResultCodes)
      */
      void finished(const QString &requestId, const int resultCode);
      /*!
      * \brief notifyStatus
      * Сигнал испускается при изменеии статуса оповещения абонента.
      * \param notifyId
      * Идентификатор оповещения (задаётся в методе addPhoneToNotify(...))
      * \param timestamp
      * Время изменения статуса
      * \param status
      * Статус оповещения (см. enum NotifyStatuses)
      */
      void notifyStatus(const QString &notifyId, const int status);
signals:

public slots:

};

#endif // ASTERISKCLIENT_H
