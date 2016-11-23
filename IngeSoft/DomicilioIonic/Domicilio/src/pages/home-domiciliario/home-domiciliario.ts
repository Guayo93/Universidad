import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { DomicilioService } from '../../providers/domicilio-service'
import { ModalConfigPage } from '../modal-config/modal-config'
import { LoginPage } from '../login/login'
import { HomeCompradorPage } from '../home-comprador/home-comprador'

@Component({
  selector: 'page-home-domiciliario',
  templateUrl: 'home-domiciliario.html',
  providers: [DomicilioService]
})

export class HomeDomiciliarioPage
{
  public orders : any;
  public status : string;

  email : string;
  id : number;
  name : string;
  lastName : string;
  phone : string;
  rootPage: any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public domicilioService: DomicilioService)
  {
    this.email = this.navParams.get('email');
    this.id = this.navParams.get('id');
    this.lastName = this.navParams.get('last_name');
    this.name = this.navParams.get('name');
    this.phone = this.navParams.get('phone');

    this.domicilioService.obtenerOrdenes(this.id, 'hold')
      .then(response =>
        {
          this.orders = response;
        }
      );
  }

  pushConfig()
  {
    this.navCtrl.push(ModalConfigPage);
  }

  signout()
  {
    this.navCtrl.setRoot(LoginPage);
  }

  switchMode()
  {
    this.navCtrl.setRoot(HomeCompradorPage, this.navParams);
  }

  getOrders()
  {
    this.domicilioService.obtenerOrdenes(this.id, this.status)
      .then(response =>
        {
          this.orders = response;
        }
      );
  }
}
