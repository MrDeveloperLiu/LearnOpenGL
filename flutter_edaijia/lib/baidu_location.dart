//location
import 'package:flutter_bmflocation/bdmap_location_flutter_plugin.dart';
import 'package:flutter_bmflocation/flutter_baidu_location_android_option.dart';
import 'package:flutter_bmflocation/flutter_baidu_location_ios_option.dart';

class BaiduLocationManager  {

  LocationFlutterPlugin locationPlugin = LocationFlutterPlugin();
  Map<String, Object>? currentLocation;

  BaiduLocationManager() {
    prepare();
    permission();
    prepare();
  }

  void permission() {
    //请求定位权限
    locationPlugin.requestPermission();
    //注册回调
    locationPlugin.onResultCallback().listen((event) {
      currentLocation = event;
      print("on location: $event");
    });
  }


  void prepare() {
    //设置iOS端AK, Android端AK可以直接在清单文件中配置
    BaiduLocationAndroidOption androidOption = new BaiduLocationAndroidOption();
    androidOption.setCoorType("bd09ll");
    androidOption.setIsNeedAltitude(true);
    androidOption.setIsNeedAddres(true);
    androidOption.setIsNeedLocationPoiList(true);
    androidOption.setIsNeedNewVersionRgc(true);
    androidOption.setIsNeedLocationDescribe(true);
    androidOption.setOpenGps(true);
    androidOption.setLocationMode(LocationMode.Hight_Accuracy);
    androidOption.setScanspan(1000);
    //ios配置
    BaiduLocationIOSOption iosOption = new BaiduLocationIOSOption();
    iosOption.setIsNeedNewVersionRgc(true);
    iosOption.setBMKLocationCoordinateType("BMKLocationCoordinateTypeBMK09LL");
    iosOption.setActivityType("CLActivityTypeAutomotiveNavigation");
    iosOption.setDesiredAccuracy("kCLLocationAccuracyBest");
    iosOption.setLocationTimeout(10);
    iosOption.setReGeocodeTimeout(10);
    iosOption.setPauseLocUpdateAutomatically(true);
    iosOption.setAllowsBackgroundLocationUpdates(true);
    iosOption.setDistanceFilter(10);

    locationPlugin.prepareLoc(androidOption.getMap(), iosOption.getMap());
  }

  void start() {
    //开始定位
    locationPlugin.startLocation();
  }

  void stop() {
    //结束定位
    locationPlugin.stopLocation();
  }

}
