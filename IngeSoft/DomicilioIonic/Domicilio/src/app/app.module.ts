import { NgModule } from '@angular/core';
import { IonicApp, IonicModule } from 'ionic-angular';
import { MyApp } from './app.component';
import { LoginPage } from '../pages/login/login';
import { ModalRegisterPage } from '../pages/modal-register/modal-register'
import { ModeSelectorPage } from '../pages/mode-selector/mode-selector'
import { HomeCompradorPage } from '../pages/home-comprador/home-comprador'
import { HomeDomiciliarioPage } from '../pages/home-domiciliario/home-domiciliario'
import { ModalNewOrderPage } from '../pages/modal-new-order/modal-new-order'
import { ModalConfigPage } from '../pages/modal-config/modal-config'
import { DomicilioService } from '../providers/domicilio-service'

@NgModule({
  declarations: [
    MyApp,
    LoginPage,
    ModalRegisterPage,
    ModeSelectorPage,
    HomeCompradorPage,
    HomeDomiciliarioPage,
    ModalNewOrderPage,
    ModalConfigPage
  ],
  imports: [
    IonicModule.forRoot(MyApp)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp,
    LoginPage,
    ModalRegisterPage,
    ModeSelectorPage,
    HomeCompradorPage,
    HomeDomiciliarioPage,
    ModalNewOrderPage,
    ModalConfigPage
  ],
  providers: [DomicilioService]
})
export class AppModule {}
