# coding = utf-8
 
from flask import Flask, render_template 
 
app = Flask(__name__)
 
@app.route("/")
def home():
    return render_template('img_static.html')
 
if __name__ == "__main__":
    app.run()
