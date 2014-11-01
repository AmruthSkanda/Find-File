#!/usr/bin/env python

# example entry.py
import pygtk
pygtk.require('2.0')
import gtk
import os

# -------------------------

class TextViewExample:

    def close_application(self, widget):
        gtk.main_quit()

    def __init__(self,wid):
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.connect("destroy", self.close_application)
        window.set_position(gtk.WIN_POS_CENTER)
        window.set_title("Search result")
        window.set_border_width(0)
        window.set_size_request(400, 540)
        window.set_resizable(True)  

        box1 = gtk.VBox(False, 0)
        window.add(box1)
        box1.show()


        box2 = gtk.VBox(False, 10)
        box2.set_border_width(10)
        box1.pack_start(box2, True, True, 0)
        box2.show()

        sw = gtk.ScrolledWindow()
        sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        textview = gtk.TextView()
        textbuffer = textview.get_buffer()
        textview.set_editable(False)
        textview.set_cursor_visible(False)
        textview.set_wrap_mode(gtk.WRAP_WORD)
        sw.add(textview)
        sw.show()
        textview.show()

        box2.pack_start(sw)

        infile = open(wid, "r")

        if infile:
            string = infile.read()
            infile.close()
            textbuffer.set_text(string)

        window.show()

def main2():
    gtk.main()

    return 0
#--------------------------

class EntryExample:
    def enter_callback(self, widget, entry, entry2,entry3):
        entry_text = entry.get_text()
        entry_text2 = entry2.get_text()
        entry_text3 = entry3.get_text()
        print "Entry contents: %s\n" % entry_text
        if(self.dirs == 0 and self.dirf == 0):
            os.system("findfile \"%s\"" % entry_text)
        elif(self.dirf == 1):
            os.system("findfile -f \"%s\" \"%s\"" % (entry_text3, entry_text))
            TextViewExample(entry_text3)
            main2()
        else :
            os.system("findfile -d \"%s\" \"%s\"" % (entry_text2, entry_text))

    def callback(self, widget, data):
        entry_text = entry.get_text()
        print "Hello again - %s was pressed" % entry_text

    def createdb(self, widget, wind):
        title="Search Database"
        message="Database is being created..."

        dialog = gtk.MessageDialog(wind,
                               gtk.DIALOG_MODAL,
                               type=gtk.MESSAGE_INFO,
                               buttons=gtk.BUTTONS_OK)
        dialog.set_markup("<b>%s</b>" % title)
        dialog.format_secondary_markup(message)
        dialog.run()
        dialog.destroy()
        os.system("findfile -db")
        dialog = gtk.MessageDialog(wind,
                               gtk.DIALOG_MODAL,
                               type=gtk.MESSAGE_INFO,
                               buttons=gtk.BUTTONS_OK)
        dialog.set_markup("<b>%s</b>" % title)
        message="Database is created..."
        dialog.format_secondary_markup(message)
        dialog.run()
        dialog.destroy()

    def aboutdig(self, widget, wind):
        title="About the program"
        message="Program to search files and folders... By : Vishnu, Amruth and Akash"
        dialog = gtk.MessageDialog(wind,
                               gtk.DIALOG_MODAL,
                               type=gtk.MESSAGE_INFO,
                               buttons=gtk.BUTTONS_OK)
        dialog.set_markup("<b>%s</b>" % title)
        dialog.format_secondary_markup(message)
        dialog.run()
        dialog.destroy()

    def entry_toggle_editable(self, checkbutton, entry2):
        #entry2.set_editable(checkbutton.get_active())
        if(self.dirs == 1):
            entry2.set_editable(checkbutton.get_active())
            entry2.hide()
            self.dirs=0
        else:
            entry2.set_editable(checkbutton.get_active())
            entry2.show()
            self.dirs=1

    def entry_toggle_editable2(self, checkbutton, entry2):
        #entry2.set_editable(checkbutton.get_active())
        if(self.dirf == 1):
            entry2.set_editable(checkbutton.get_active())
            entry2.hide()
            self.dirf=0
        else:
            entry2.set_editable(checkbutton.get_active())
            entry2.show()
            self.dirf=1


    def __init__(self):
        # create a new window
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        #window.set_size_request(200, 240)
        window.set_title("File search")
        window.connect("delete_event", lambda w,e: gtk.main_quit())
        window.set_position(gtk.WIN_POS_CENTER)
        window.set_border_width(15)
        self.dirs=0
        self.dirf=0

        vbox = gtk.VBox(False, 10)
        window.add(vbox)
        vbox.show()

        entry2 = gtk.Entry()
        entry2.set_max_length(50)
        entry2.connect("activate", self.enter_callback, entry2)
        entry2.set_text("Directory")
        #entry2.insert_text("", len(entry2.get_text()))
        entry2.select_region(0, len(entry2.get_text()))

        # ---------------------------
        entry3 = gtk.Entry()
        entry3.set_max_length(50)
        entry3.connect("activate", self.enter_callback, entry3)
        entry3.set_text("file out")
        #entry2.insert_text("", len(entry2.get_text()))
        entry3.select_region(0, len(entry3.get_text()))
        # ----------------------------

        entry = gtk.Entry()
        entry.set_max_length(50)
        entry.connect("activate", self.enter_callback, entry, entry2,entry3)


        entry.set_text("File ")
        entry.insert_text("name", len(entry.get_text()))
        entry.select_region(0, len(entry.get_text()))
        vbox.pack_start(entry, False, False, 0)

        entry.show()

        hbox = gtk.HBox(False, 0)
        vbox.add(hbox)
        hbox.show()
                                  
        check = gtk.CheckButton("Directory")
        hbox.pack_start(check, False, False, 0)
        vbox.pack_start(entry2, False, False, 0)
        #entry2.show()
        check.connect("toggled", self.entry_toggle_editable, entry2)
        #print dirs
        check.set_active(False)
        check.show()

        #-----------------
        check2 = gtk.CheckButton("File out")
        hbox.pack_start(check2, False, False, 0)
        vbox.pack_start(entry3, False, False, 0)
        entry3.show()
        check2.connect("toggled", self.entry_toggle_editable2, entry3)
        #print dirs
        check2.set_active(True)
        check2.show()
        #---------------------


        self.search = gtk.Button("Search")
        self.search.connect("clicked", self.enter_callback, entry, entry2,entry3)
        vbox.pack_start(self.search, False, False, 0)
        self.search.show()


        self.database = gtk.Button("Database")
        self.database.connect("clicked", self.createdb, window)
        vbox.pack_start(self.database, False, False, 0)
        self.database.show()


        self.about = gtk.Button("About")
        self.about.connect("clicked", self.aboutdig, window)
        vbox.pack_start(self.about, False, False, 0)
        self.about.show()
                                   
        button = gtk.Button(stock=gtk.STOCK_CLOSE)
        button.connect("clicked", lambda w: gtk.main_quit())
        vbox.pack_start(button, False, False, 0)
        button.set_flags(gtk.CAN_DEFAULT)
        button.grab_default()
        button.show()
        window.show()

def main():
    gtk.main()
    return 0

if __name__ == "__main__":
    EntryExample()
    main()