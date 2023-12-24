const server_url = "ws://localhost:3000";

// js for fast debugging? (at least won't need to set up jsx tooling)
function CreateButton(label, callback) {
  const el = document.createElement('button');
  el.innerText = label;
  el.addEventListener('click', callback);
  return el;
}

class ClientInstance {
  constructor() {
    this.ws = null;
    const body =  document.createElement('div');
    const info = {
      'logs': document.createElement('div'),
      'room': document.createElement('div'),
    };
    this.element = {
      'info': document.createElement('div'),
      'connect': CreateButton("Connect", () => this.Connect()),
      'disconnect': CreateButton("Disconnect", () => this.Disconnect()),
      'payload': document.createElement('input'),
      'send': CreateButton("Send", () => {
        this.Send(this.element.payload.value);
        this.element.payload.value = "";
      }),
    };
    this.element.info.append(...Object.values(info));
    this.element.info.classList.add('info');
    body.append(...Object.values(this.element));
    this.element = Object.assign(this.element, info);
    this.element.body = body;
    console.log(this.element)
    this.logs = [];
    for(let i = 0; i < 10; i ++) this.PushLog(-1, '');
  }
  Connect() {
    if(this.ws) this.Disconnect();
    this.ws = new WebSocket(server_url);
    this.ws.onopen = (event) => {
      this.PushLog(event.timeStamp, 'socket opened');
    }
    this.ws.onclose = (event) => {
      this.PushLog(event.timeStamp, 'socket closed');
    }
    this.ws.onerror = (event) => {
      console.warn(event);
      this.PushLog(event.timeStamp, 'socket error');
    }
    this.ws.onmessage = (event) => {
      console.log('data', event.data);
      this.PushLog(event.timeStamp, `<- ${event.data}`);
    }
  }
  Disconnect() {
    this.ws.close();
    this.ws = null;
  }
  PushLog(time, log) {
    this.logs.push(`[${(~~time).toString().padStart(6, '_')}] ${log}`);
    this.element.logs.innerText = this.logs.slice(-10).join('\n');
  }
  Send(data) {
    if(!this.ws) throw 'socket is not open; cannot send';
    this.ws.send(data);
    this.PushLog(new Event('').timeStamp, `-> ${data}`)
  }
}

const c = new ClientInstance();
document.body.append(c.element.body);

const c2 = [...new Array(2)].map(x => {
  const client = new ClientInstance();
  document.body.append(client.element.body);
  return client;
});
