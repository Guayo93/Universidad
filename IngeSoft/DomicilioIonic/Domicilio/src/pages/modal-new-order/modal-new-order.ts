import { Component } from '@angular/core';
import { NavController, NavParams, AlertController } from 'ionic-angular';
import { DomicilioService } from '../../providers/domicilio-service'
import { HomeCompradorPage } from '../home-comprador/home-comprador'

@Component({
  selector: 'page-modal-new-order',
  templateUrl: 'modal-new-order.html',
  providers: [DomicilioService]
})

export class ModalNewOrderPage
{
  order : string;
  address : string;
  comments : string;
  id : number;

  resp : any;
  compradorPage : HomeCompradorPage;

  constructor(public navCtrl: NavController, public navParams: NavParams, public domicilioService: DomicilioService, public alertController: AlertController)
  {
    this.id = this.navParams.get('id');
  }

  sendOrder()
  {
    this.domicilioService.crearOrden(this.id, this.address, this.order, this.comments)
      .then(response =>
        {
          this.resp = response;

          if(typeof this.resp === "string" && this.resp.includes('errors'))
          {
            let alert = this.alertController.create(
              {
                title: 'Error',
                subTitle: 'Ocurrio un error con su solicitud.',
                buttons: ['Entiendo']
              }
            );
            alert.present();
          }
          else
          {
            let alert = this.alertController.create(
              {
                title: 'Exito',
                subTitle: 'Su orden se ha creado exitosamente.',
                buttons: ['Confirmar']
              }
            );
            alert.present();

            this.compradorPage.getOrders();
            this.navCtrl.pop();
          }
        }
      );
  }
}
