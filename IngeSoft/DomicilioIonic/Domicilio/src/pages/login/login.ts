import { Component } from '@angular/core';
import { NavController, AlertController } from 'ionic-angular';
import { ModeSelectorPage } from '../mode-selector/mode-selector'
import { ModalRegisterPage } from '../modal-register/modal-register'
import { DomicilioService } from '../../providers/domicilio-service'

@Component({
  selector: 'page-login',
  templateUrl: 'login.html',
  providers: [DomicilioService]
})

export class LoginPage
{
  email : string;
  pass : string;

  resp : any;

  constructor(public navCtrl: NavController, public domicilioService: DomicilioService, public alertCtrl: AlertController)
  {

  }

  validateUser()
  {
    this.domicilioService.validarUsuario(this.email, this.pass)
      .then(response =>
      {
        this.resp = response;

        if(typeof this.resp === "string" && this.resp.includes('e-mail') === true)
        {
          let alert = this.alertCtrl.create(
            {
              title: 'Error',
              subTitle: 'El correo ingresado no esta registrado.',
              buttons: ['Entiendo']
            }
          );
          alert.present();
        }
        else if(typeof this.resp === "string" && this.resp.includes('password') === true)
        {
          let alert = this.alertCtrl.create(
            {
              title: 'Error',
              subTitle: 'La contraseña ingresada es incorrecta.',
              buttons: ['Entiendo']
            }
          );
          alert.present();
        }
        else
        {
          this.navCtrl.push(ModeSelectorPage, this.resp);
        }
      }
    );
  }

  pushRegister()
  {
    this.navCtrl.push(ModalRegisterPage);
  }
}
