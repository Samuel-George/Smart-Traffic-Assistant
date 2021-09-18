#----------------------------------------------------------------------------#
# Imports
#----------------------------------------------------------------------------#

import os
from logging import Formatter, FileHandler
from config import  app
from flask import (
render_template)
from routes import (
navigation_routes,
park_routes,
tracktion_routes)


#----------------------------------------------------------------------------#
# Controllers.
#----------------------------------------------------------------------------#

@app.route('/')
def index():
  return render_template('pages/home.html')

@app.errorhandler(400)
def server_error(error):
    return render_template('errors/400.html'), 400

@app.errorhandler(401)
def server_error(error):
    return render_template('errors/401.html'), 401

@app.errorhandler(403)
def server_error(error):
    return render_template('errors/403.html'), 403

@app.errorhandler(404)
def not_found_error(error):
    return render_template('errors/404.html'), 404

@app.errorhandler(405)
def server_error(error):
    return render_template('errors/405.html'), 405

@app.errorhandler(403)
def server_error(error):
    return render_template('errors/409.html'), 409

@app.errorhandler(422)
def server_error(error):
    return render_template('errors/422.html'), 422

@app.errorhandler(500)
def server_error(error):
    return render_template('errors/500.html'), 500





if not app.debug:
    file_handler = FileHandler('error.log')
    file_handler.setFormatter(
        Formatter('%(asctime)s %(levelname)s: %(message)s [in %(pathname)s:%(lineno)d]')
    )
    app.logger.setLevel(logging.INFO)
    file_handler.setLevel(logging.INFO)
    app.logger.addHandler(file_handler)
    app.logger.info('errors')

#----------------------------------------------------------------------------#
# Launch.
#----------------------------------------------------------------------------#

# Default port:
if __name__ == '__main__':
    port = int(os.environ.get("PORT", 5000))
    app.run(debug=True, host='0.0.0.0', port=port)
