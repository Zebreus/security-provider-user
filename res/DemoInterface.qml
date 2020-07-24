import QtQuick 2.4
import org.UserBackend 1.0

DemoInterfaceForm {
    id: demoForm
    UserBackend{
        id: backend
    }

    providerUrlField{
        text: backend.providerUrl
    }

    serverUrlField{
        text: backend.serverUrl
    }

    usernameField{
        text: backend.username
    }

    passwordField{
        text: backend.password
    }

    tokenField{
        text: backend.token
    }

    loggedIn{
        checked: backend.loggedIn
    }

    Connections{
        target: obtainButton
        onPressed: {
            backend.username = usernameField.text;
            backend.password = passwordField.text;
            backend.providerUrl = providerUrlField.text;
            backend.obtainToken();
        }
    }

    Connections{
        target: loginButton
        onPressed: {
            backend.serverUrl = serverUrlField.text;
            backend.login();
        }
    }
}
