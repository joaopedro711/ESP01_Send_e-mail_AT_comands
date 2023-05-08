//funcao completa que chama todos os comandos e dá um atraso
void send_email(){
    esp_mode();
    delay_seg(1);

    esp_connect();
    delay_seg(1);

    esp_enable_MUX();
    delay_seg(1);

    esp_create_server();
    delay_seg(1);

    esp_connect_SMPT2GO();
    delay_seg(1);

    esp_login_mail();
    delay_seg(1);

    esp_mail_sendID();
    delay_seg(1);

    esp_mail_recID();
    delay_seg(1);

    esp_start_mail();
    delay_seg(1);


    esp_mail_subject();
    delay_seg(1);

    esp_mail_body();
    delay_seg(1);

    esp_End_mail();
    delay_seg(1);

    esp_disconnect_SMPT2GO();
    delay_seg(2);
    delay_seg(10);
}



// WIFI Mode (station/softAP/station+softAP) (AT+CWMODE)
//Esta função irá definir o ESP8266 no modo 3. O que significa que o módulo agora pode atuar como um ponto de acesso e também como um servidor.
void esp_mode(){
    gprs_str("AT+CWMODE=3\r\n");
}

// Conecta ao wifi
void esp_connect(){
//    gprs_str("AT+CWJAP=\"");
//    gprs_str(SSID);
//    gprs_str("\",\"");
//    gprs_str(PASSWORD);
//    gprs_str("\"\r\n");
    gprs_str("AT+CWJAP=\"Netvirtua_VERA\",\"40225295022\"");
}

//Funcao para ativar multiplas conexoes
void esp_enable_MUX(){
    gprs_str("AT+CIPMUX=1\r\n");
}

// inicia um servidor na porta 80
void esp_create_server(){
    gprs_str("AT+CIPSERVER=1,80\r\n");
}

// esta função, estabelece uma conexão TCP com SMPT2GO. Uma vez que a conexão é estabelecida, esta função também se move para a página de Login do site.
void esp_connect_SMPT2GO(){
    gprs_str("AT+CIPSTART=4,\"TCP\",\"mail.smtp2go.com\",2525\r\n");

    gprs_str("AT+CIPSEND=4,20\r\n");

    gprs_str("EHLO 192.168.1.123\r\n");

    gprs_str("AT+CIPSEND=4,12\r\n");

    gprs_str("AUTH LOGIN\r\n");
}

//função para inserir ID de e-mail e senha no formato base 64. e-mail do remetente
//34 é a quantidade de caracteres sendo 2 de (\r \n)
//190057807@aluno.unb.br = MTkwMDU3ODA3QGFsdW5vLnVuYi5icg=== (base64)
// senha: arapukamovel = YXJhcHVrYW1vdmVs (base 64)
//18 é a quantidade de caracteres sendo 2 de (\r \n)
void esp_login_mail(){
    //user
    gprs_str("AT+CIPSEND=4,34\r\n");
    gprs_str("MTkwMDU3ODA3QGFsdW5vLnVuYi5icg==\r\n");

    //senha
    gprs_str("AT+CIPSEND=4,18\r\n");
    gprs_str("YXJhcHVrYW1vdmVs\r\n");
}




//Essa função é usada para definir o nome da ID do remetente.
//36 é a quantidade de caracteres sendo 2 de (\r \n)
void esp_mail_sendID(){
    gprs_str("AT+CIPSEND=4,36\r\n");
    gprs_str("MAIL FROM:<190057807@aluno.unb.br>\r\n");
}


//Essa função é usada para definir o nome do ID do receptor
//RCPT To:<jo88791@gmail.com> = tem 27 caracteres + 2 de (\r \n)
void esp_mail_recID(){
    gprs_str("AT+CIPSEND=4,29\r\n");
    gprs_str("RCPT To:<jo88791@gmail.com>\r\n");
}


//Esta função instrui o servidor SMPT2GO que vamos alimentar o assunto e o corpo do e-mail e o prepara para o mesmo.
// Data = 4 caracteres + 2 de (\r\n)
void esp_start_mail(){
    gprs_str("AT+CIPSEND=4,6\r\n");
    gprs_str("DATA\r\n");

}

//Essa função é usada para definir o assunto do e-mail
//Subject: Teste = 14 caracteres + 2 de (\r\n)
void esp_mail_subject(){
    gprs_str("AT+CIPSEND=4,16");
    gprs_str("Subject: Teste");
}


//Inserir o corpo do e-mail
// a mensagem tem 25 caracteres + 2 de (\r\n)
void esp_mail_body(){
    gprs_str("AT+CIPSEND=4,27");
    gprs_str("Funcionou, Graças a Deus!");
}


// instrui o servidor SMPT2GO que terminamos de adicionar detalhes ao e-mail e envia.
// tem apenas 3 caracteres
void esp_End_mail(){
    gprs_str("AT+CIPSEND=4,3\r\n");
    gprs_str(".\r\n");
}

//depois de enviar o e-mail, temos que encerrar a conexão TCP com o servidor SMPT2GO.
void esp_disconnect_SMPT2GO(){
    gprs_str("AT+CIPSEND=4,6\r\n");
    gprs_str("QUIT\r\n");
}
