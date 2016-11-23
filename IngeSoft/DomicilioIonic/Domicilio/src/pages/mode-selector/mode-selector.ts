import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HomeCompradorPage } from '../home-comprador/home-comprador'
import { HomeDomiciliarioPage } from '../home-domiciliario/home-domiciliario'

@Component({
  selector: 'page-mode-selector',
  templateUrl: 'mode-selector.html'
})
export class ModeSelectorPage
{
  constructor(public navCtrl: NavController, public navParams: NavParams) {}

  activateComprador()
  {
    this.navCtrl.setRoot(HomeCompradorPage, this.navParams);
  }

  activateDomiciliario()
  {
    this.navCtrl.setRoot(HomeDomiciliarioPage, this.navParams);
  }
}
