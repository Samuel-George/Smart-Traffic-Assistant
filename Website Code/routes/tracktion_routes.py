import folium
from config import app
from flask import (
    render_template,
    request
)


#  Shows
#  ----------------------------------------------------------------

@app.route('/tracktion', methods = ['POST', 'GET'])
def track():
  if request.method == 'POST':
    ID = int(request.form['id'])

    if ID == 1:
      with open('GSM','r') as file:
        if file:
          Lines = file.readlines()[0].split(' ')
          long = float(Lines[0])
          lat = float(Lines[0])
    else:
      return render_template('errors/401.html')

    map = folium.Map(location=[long, lat],
    zoom_start=13)

    folium.Marker(location=[long, lat],
    popup="<b>Marker here</b>",
    tooltip="Click Here!").add_to(map)
    return map._repr_html_()
  else:
    return render_template('pages/tracktion.html')
