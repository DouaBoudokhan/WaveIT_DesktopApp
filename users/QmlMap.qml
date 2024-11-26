import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.9
Rectangle
{
    id:window
    property double latitude:0
    property double longitude:0
    property Component locationmarker: locmarker
    Plugin
    {
        id:googlemapview
        name:"osm"
    }
    Map
    {
        id:mapview
        anchors.fill: parent
        plugin: googlemapview
        center: QtPositioning.coordinate(latitude,longitude)
        zoomLevel:15
    }
    function setCenterPosition(lati,longi)
    {
        mapview.pan(latitude - lati, longitude - longi)
        latitude = lati
        longitude = longi
    }
    function setLocationMarking(lati,longi)
    {
        var item = locationmarker.createObject(window, {
                                               coordinate:QtPositioning.coordinate(lati,longi)
                                               })
        mapview.addMapItem(item)
    }
    Component
    {
        id:locmarker
        MapQuickItem
        {
            id:markerimg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position
            sourceItem: Image {
                id: image
                width: 20
                height: 20
                source: "/img/img/img.png"
            }
        }
    }
}
