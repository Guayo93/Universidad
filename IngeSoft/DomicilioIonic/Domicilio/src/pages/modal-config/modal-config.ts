import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';

@Component({
  selector: 'page-modal-config',
  templateUrl: 'modal-config.html'
})

export class ModalConfigPage
{
  tel : string;
  pass : string;
  passConfirm : string;

  constructor(public navCtrl: NavController, public navParams: NavParams) {}

  update()
  {

  }

  deleteAccount()
  {

  }
}
