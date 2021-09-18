from config import app
from flask import (
    render_template,
    request,

)
import math
import folium
import time
pi = math.pi

@app.route('/navigation', methods = ['POST', 'GET'])
def navigation():
  
  long = 0
  lat = 0
  distance = 0
  if request.method == 'POST':

    traffic_lon = 30.008366
    traffic_lat = 31.169875
    if request.form['longtiude'] and request.form['latitude']:
      long = float(request.form['longtiude'])
      lat = float(request.form['latitude'])
    else:
      return render_template('pages/navigation.html')

    radius = 6371

    lat1 = lat * pi / 180
    lat2 = traffic_lat * pi / 180
    lon1 = long * pi / 180
    lon2 = traffic_lon * pi / 180
    deltaLat = lat2 - lat1
    deltaLon = lon2 - lon1

    x = deltaLon * math.cos((lat1 + lat2) / 2)
    y = deltaLat

    distance = round(radius * math.sqrt(x * x + y * y) * 1000)

    with open(f'traffic.txt','r') as file:
      if file:
        Lines = file.readlines()

    data = {'distance' : distance,
            'status': Lines[0] }

    return render_template('pages/navigation.html', data=data)

  else:
    return render_template('pages/navigation.html')


@app.route('/navigation/<location>')
def nav_info(location):

  arr = location.split('-')
  long = float(arr[0])
  lat = float(arr[1])

  a_file = open("GSM", "w")
  a_file.truncate()
  a_file.write(f'{long} {lat}')
  a_file.close()

  return 'OK'

@app.route('/navigation/gsm')
def gsm():
  with open('GSM','r') as file:
    if file:
      Lines = file.readlines()[0].split(' ')
      long = float(Lines[0])
      lat = float(Lines[1])
    else:
      return render_template('pages/navigation.html')

  map = folium.Map(location=[long, lat],
    zoom_start=13)

  folium.Marker(location=[long, lat],
  popup="<b>Marker here</b>",
  tooltip="Click Here!").add_to(map)

  
  return map._repr_html_()