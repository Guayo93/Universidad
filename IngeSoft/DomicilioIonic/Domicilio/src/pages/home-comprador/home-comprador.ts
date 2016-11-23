import { Component } from '@angular/core';
import { NavController, NavParams, MenuController } from 'ionic-angular';
import { DomicilioService } from '../../providers/domicilio-service'
import { ModalNewOrderPage } from '../modal-new-order/modal-new-order'
import { HomeDomiciliarioPage } from '../home-domiciliario/home-domiciliario'
import { ModalConfigPage } from '../modal-config/modal-config'
import { LoginPage } from '../login/login'

@Component({
  selector: 'page-home-comprador',
  templateUrl: 'home-comprador.html',
  providers: [DomicilioService]
})

export class HomeCompradorPage
{
  public orders : any;
  public status : string;
  public content : any;

  email : string;
  id : number;
  lastName : string;
  name : string;
  phone : string;

  rootPage : any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public menuController: MenuController, public domicilioService: DomicilioService)
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

  public getOrders()
  {
    this.domicilioService.obtenerOrdenes(this.id, this.status)
      .then(response =>
        {
          this.orders = response;
        }
      )
  }

  addOrder()
  {
    this.navCtrl.push(ModalNewOrderPage);
  }

  switchMode()
  {
    this.navCtrl.setRoot(HomeDomiciliarioPage, this.navParams);
  }

  pushConfig()
  {
    this.navCtrl.push(ModalConfigPage);
  }

  signout()
  {
    this.navCtrl.setRoot(LoginPage);
  }
}
