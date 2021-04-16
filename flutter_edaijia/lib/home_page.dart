import 'dart:ui';
import 'package:flutter/material.dart';
import 'package:flutter_baidu_mapapi_base/flutter_baidu_mapapi_base.dart';
import 'package:flutter_baidu_mapapi_map/flutter_baidu_mapapi_map.dart';
import 'baidu_location.dart';
import 'view_const.dart';

class HomePage {

  BaiduLocationManager locationManager = BaiduLocationManager();
  BMFMapController? mapController;


  HomePage () {
    locationManager.start();
  }

  Scaffold getScaffold () {
    return Scaffold(
      appBar: getBar(),
      body: getBody(),
      drawer: Drawer(
        child: Column(
          children: [
            Text("1"),
            Text("2"),
            Text("3"),
          ],
        ),
      ), //抽屉

    );
  }

  AppBar getBar() {
    return AppBar(

      title: Text("Flutter demo"),

    );
  }

  Widget getBody() {
    return Stack(
      alignment: AlignmentDirectional.bottomCenter,
      children: [

        Container(
          height: ViewConst.screenSize.width,
          width: ViewConst.screenSize.height,

          child: BMFMapWidget(

            onBMFMapCreated: (controller) {
              mapController = controller;
              print("地图创建成功");
            },

            mapOptions: BMFMapOptions(
              center: BMFCoordinate(39.917215, 116.380341),
              zoomLevel: 19,
              mapPadding: BMFEdgeInsets(left: 30, top: 0, right: 30, bottom: 0),
              rotateEnabled: false,
              overlookEnabled: false,
              zoomEnabledWithDoubleClick: false,
              zoomEnabledWithTap: false,
            ),
          ),
        ),

        Container(
          color: Color.fromARGB(0x10, 0x00, 0x00, 0x00),
          child: ListView(
            itemExtent: 50,
            shrinkWrap: true,
            padding: const EdgeInsets.all(20.0),
            children: [
              const Text('I\'m dedicating every day to you'),
              const Text('Domestic life was never quite my style'),
              const Text('When you smile, you knock me out, I fall apart'),
              const Text('And I thought I was so smart'),
            ],
          ),
        ),

        Container(
          child: Positioned(
            right: 10,
            bottom: 50,
            child: TextButton(
              child: Text('Location'),
              style: ButtonStyle(
                backgroundColor: MaterialStateProperty.all<Color>(Colors.white),
              ),
              onPressed: (){
                Map<String, Object>? location = locationManager.currentLocation;
                if (mapController != null && location != null){
                  mapController!.setCenterCoordinate(BMFCoordinate.fromMap(location), true);
                }
              },
            ),
          ),

        )

      ],
    );
  }


}
