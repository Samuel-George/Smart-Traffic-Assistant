from config import app
from flask import (
    render_template
)



@app.route('/parks')
def parks():
  return render_template('pages/parks.html')