var helper;
var components = [];
var properties = [];
var channels = [];
var supported = [
  { name: 'status', class: 'com.muzzley.properties.status', schema: ['//ontology.muzzley.com/schemas/v1/status-onoff'] }
];
var EVENT_START = 'touchstart';
var EVENT_RELEASE = 'touchend';

if('ontouchstart' in window) {
  EVENT_START = 'touchstart';
  EVENT_RELEASE = 'touchend';
} else if (window.navigator.pointerEnabled) {
  EVENT_START = 'pointerdown';
  EVENT_RELEASE = 'pointerup';
} else if (window.navigator.msPointerEnabled) {
  EVENT_START = 'MSPointerDown';
  EVENT_RELEASE = 'MSPointerUp';
} else {
  EVENT_START = 'mousedown';
  EVENT_RELEASE = 'mouseup';
}

muzzley.ready(function (options) {
  if(!options || !options.channels){
    return alert('There is no channels data');
  }
  console.log(options.channels);
  channels = options.channels;
  helper = new ChannelsHelper(true, false);
  channelsMessage(channels);
});

function channelsMessage(data) {
  channels = data;
  console.log('channels', channels);
  console.log(channels);
  components = helper.getComponentsFromChannels(channels);
  properties = helper.getPropertiesFromChannels(supported, false);
  console.log('properties');
  console.log(properties);
  userConnected();
}

function userConnected() {
    var subscription = muzzley.subscribe({
    namespace: 'iot',
    payload: {
      profile: components[0].profile,
      channel: components[0].channel
    }
  });
    subscription.on('subscribe', function () {
      //console.log('subscribe');
    });
    subscription.on('message', onMessage);
}

function onMessage(message){
  var payload = message.getPayload();
 console.log('Message received ', payload);
  var channel = payload.channel;
  var property = payload.property;
  var data = payload.data;
  if(data === null || data === undefined){
    return console.log('Data is empty');
  }
  var component = payload.component;
  var classs = helper.getClassById(property, channel, component);
  var value = data.value;
  console.log("-- "+property, component, value);
  if(property === properties[0].id){
    setStatus(value);
  }
}


$(document).ready(function() {
  var partialW = window.innerWidth;
  var partialH = window.innerHeight;
  $('body').css({height: partialH+'px', weight: partialW+'px'});
  var margin = (window.innerHeight*.5) - ($('.container-button').height()*.5);
  $('.container-button').css('margin-top', margin+'px');
});

function setStatus(value){
    if(value === true){
        $('#open-button').removeClass();
        $('#open-button').addClass('down');
        $('#open-button span').text('Close');
    }else if(value === false){
        $('#open-button').removeClass();
        $('#open-button').addClass('up');
        $('#open-button span').text('Open');
    }
}

$('#open-button').on(EVENT_START, function(){
    setStatus(true);
    var data = {
        namespace: 'iot',
        payload: {
            io: 'w',
            profile: channels[0].profileId, 
            channel: channels[0].remoteId, 
            component: properties[0].component,
            property: properties[0].id,
            data: {value: true}
        }
    };
    console.log(EVENT_START, data);
    muzzley.publish(data);
});

$('#open-button').on(EVENT_RELEASE, function(){
    setStatus(false);
    var data = {
        namespace: 'iot',
        payload: {
            io: 'w',
            profile: channels[0].profileId, 
            channel: channels[0].remoteId, 
            component: properties[0].component,
            property: properties[0].id,
            data: {value: false}
        }
    };
    console.log(EVENT_RELEASE, data);
    muzzley.publish(data);
});
