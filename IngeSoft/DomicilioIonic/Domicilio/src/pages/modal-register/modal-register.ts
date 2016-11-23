import { Component } from '@angular/core';
import { NavController, AlertController } from 'ionic-angular';
import { DomicilioService } from '../../providers/domicilio-service'

@Component({
  selector: 'page-modal-register',
  templateUrl: 'modal-register.html',
  providers: [DomicilioService]
})

export class ModalRegisterPage
{
  name : string;
  lastName : string;
  email : string;
  phone : string;
  pass : string;
  passConfirm : string;

  resp : any;

  constructor(public navCtrl: NavController, public alertCtrl: AlertController, public domicilioService: DomicilioService) {}

  register()
  {
    let alert = null;

    if(this.pass === this.passConfirm)
    {
      this.domicilioService.registarUsuario(this.name, this.lastName, this.email, this.pass, this.phone)
        .then(response =>
        {
          this.resp = response;

          if(typeof this.resp === "boolean")
          {
            alert = this.alertCtrl.create(
              {
                title: 'Error',
                subTitle: 'El correo ingresado ya esta registrado.',
                buttons: [
                  {
                    text: 'Confirmar',
                    handler: () =>
                    {
                      this.navCtrl.pop();
                    }
                  }
                ]
              }
            );
            alert.present();
          }
          else
          {
            alert = this.alertCtrl.create(
              {
                title: 'Exito',
                subTitle: 'Registro exitoso.',
                buttons: ['Confirmar']
              }
            );
            alert.present();
          }
        }
      );
    }
    else
    {
      alert = this.alertCtrl.create(
        {
          title: 'Error',
          subTitle: 'Los campos de contraseña no coinciden.',
          buttons: ['Entiendo']
        }
      );
      alert.present();
    }
  }
}
