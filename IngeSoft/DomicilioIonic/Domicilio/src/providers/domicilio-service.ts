import { Injectable } from '@angular/core';
import { Http, Headers, RequestOptions } from '@angular/http';
import 'rxjs/add/operator/map';

@Injectable()
export class DomicilioService {

  urlGen : string;
  serverResp : any;
  serverError : string;

  static get parameters()
  {
    return [[Http]];
  }

  constructor(public http: Http)
  {
    this.urlGen = 'https://domicilio-143122.appspot.com/api/';
  }

  registarUsuario(userName, userLastName, userEmail, userPass, userPhone)
  {
    let url = this.urlGen + 'users/v1';
    let body = JSON.stringify({name: userName, last_name: userLastName, email: userEmail, password: userPass, phone: userPhone});
    let header = new Headers({'Content-Type': 'application/json'});

    return new Promise(resolve =>
      {
        this.http.post(url, body, {"headers": header}).map(res => res.json()).subscribe(
          resp =>
          {
            this.serverResp = resp.results;
            resolve(this.serverResp);
          },
          error =>
          {
            this.serverError = JSON.stringify(error.json());
            resolve(false);
          }
        )
      }
    );
  }

  validarUsuario(userEmail, userPass)
  {
    let url = this.urlGen + 'users/v1/login';
    let body = JSON.stringify({email: userEmail, password: userPass});
    let header = new Headers({'Content-Type': 'application/json', 'Cache-Control': 'no-cache'});
    let options = new RequestOptions({headers: header});

    return new Promise(resolve =>
      {
        this.http.post(url, body, options).map(res => res.json()).subscribe(
          resp =>
          {
            this.serverResp = resp;
            resolve(this.serverResp);
          },
          error =>
          {
            this.serverError = JSON.stringify(error.json());
            resolve(this.serverError);
          }
        )
      }
    );
  }

  obtenerOrdenes(userID, orderStatus)
  {
    let url = this.urlGen + 'users/v1/orders/' + userID + '/' + orderStatus;

    return new Promise(resolve =>
      {
        this.http.get(url).map(res => res.json()).subscribe(
          resp =>
          {
            this.serverResp = resp;
            resolve(this.serverResp);
          },
          error =>
          {
            this.serverError = JSON.stringify(error.json());
            resolve(this.serverError);
          }
        )
      }
    );
  }

  crearOrden(userID, userLocation, userOrder, userComments)
  {
    let url = this.urlGen + 'users/v1/orders/' + userID;
    let body = JSON.stringify({location: userLocation, order: userOrder, comments: userComments});
    let header = new Headers({'Content-Type': 'application/json', 'Cache-Control': 'no-cache'});
    let options = new RequestOptions({headers: header});

    return new Promise(resolve =>
      {
        this.http.post(url, body, options).map(res => res.json()).subscribe(
          resp =>
          {
            this.serverResp = resp;
            resolve(this.serverResp);
          },
          error =>
          {
            this.serverError = JSON.stringify(error.json());
            resolve(this.serverError);
          }
        )
      }
    );
  }

  rastrearOrden()
  {

  }

  aceptarOrden(orderID, deliveryID, destinyLat, destinyLon)
  {
    let url = this.urlGen + 'orders/v1/take/' + orderID;
    let body = JSON.stringify({delivery_id: deliveryID, latitude: destinyLat, longitude: destinyLon});
    let header = new Headers({'Content-Type': 'application/json', 'Cache-Control': 'no-cache'});
    let options = new RequestOptions({headers: header});

    return this.http.put(url, body, options).map(res => res.json());
  }

  finalizarOrden(orderID, deliveryID)
  {
    let url = this.urlGen + 'orders/v1/take/' + orderID;
    let body = JSON.stringify({delivery_id: deliveryID});
    let header = new Headers({'Content-Type': 'application/json', 'Cache-Control': 'no-cache'});
    let options = new RequestOptions({headers: header});

    return this.http.put(url, body, options).map(res => res.json());
  }
}
