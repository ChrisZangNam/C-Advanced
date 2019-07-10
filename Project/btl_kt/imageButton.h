#include "btree.h"
#include"hien.h"
#include"list4.h"
GtkWidget *view;
GtkWidget *searchEntry;
GtkWidget *label;
GtkWidget *meaningTextView;

GtkWidget *addWordEntry;
GtkWidget *addMeaningEntry;
GtkWidget *addUpdateButton;

GtkWidget *editSearchEntry;
GtkWidget *editSearchButton;
GtkWidget *editMeaningEntry;
GtkWidget *editUpdateButton;

GtkWidget *deleteSearchEntry;
GtkWidget *deleteSearchButton;
GtkWidget *deleteMeaningEntry;

gchar *chaoMung="",*them="\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________________________";
char word[1000],data[1000];
GtkTextBuffer *buffer;
GtkTextIter iter;

BTA *root,*soundexTree;

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (searchEntry));
  gtk_entry_set_text (GTK_ENTRY(meaningTextView),entry_text);
}
static void enter_callback2( GtkWidget *widget,
                            GtkWidget *entry )
{
  char *e;
  int k;
  char result[100];
    e=(char*) gtk_entry_get_text (GTK_ENTRY (searchEntry));
    k=autoComplete(soundexTree,e,result);
				if(k!=0)
				gtk_entry_set_text (GTK_ENTRY(searchEntry),result);
}

static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

static void addTab( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;

    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 1);

}
static void suggestFunction( GtkButton   *button,
                         GtkNotebook *notebook )
{
    char suggest[100][100];
    char *e;
    int k,i;
    e=(char*) gtk_entry_get_text (GTK_ENTRY (searchEntry));
    k=suggestion(soundexTree,e,suggest);
    model = create_and_fill_model (suggest,k);
    if(k!=0)gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
}
static void searchMainFunction( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;
    page = gtk_notebook_get_current_page (notebook);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);
    char *e;
    e=(char*) gtk_entry_get_text (GTK_ENTRY (searchEntry));
    //g_print("\n %s",e);
    int j;
    int k=btsel(root,e,data,sizeof(data),&j);
    if(k==0) {strcat(data,them);gtk_text_buffer_set_text (buffer,data,-1);}
    else gtk_text_buffer_set_text (buffer,"*không có từ này",-1);

}

static void editSearchFunction( GtkButton   *button,
                         GtkNotebook *notebook )
{
    const gchar *entry_text;
     char *e;
    e=(char*) gtk_entry_get_text (GTK_ENTRY (editSearchEntry));
    int j;

int k=btsel(root,e,data,sizeof(data),&j);
      if(k!=0) gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),"*không có từ này");
else {
  //gtk_entry_set_text (GTK_ENTRY(editWordEntry),e);
  gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),data);
}

}
/*static void deleteSearchFunction( GtkButton   *button,
                         GtkNotebook *notebook )
{
    const gchar *entry_text;
     char *e;
    e=(char*) gtk_entry_get_text (GTK_ENTRY (deleteSearchEntry));
    int j;

int k=btsel(root,e,data,sizeof(data),&j);
      if(k!=0) gtk_text_buffer_set_text (buffer,"tu khong ton tai",-1);
else {
  gtk_entry_set_text (GTK_ENTRY(deleteWordEntry),e);
  gtk_entry_set_text (GTK_ENTRY(deleteMeaningEntry),data);
}

}*/

static void editUpdateFunction( GtkButton   *button,
                         GtkNotebook *notebook )
{
    char *e,*f;

   e=(char*) gtk_entry_get_text (GTK_ENTRY (editSearchEntry));
      f=(char*) gtk_entry_get_text (GTK_ENTRY (editMeaningEntry));
      int i=btupd(root,e,f,sizeof(data));
  if(i!=0) gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),"*sửa ko thành công  ");
  else gtk_entry_set_text (GTK_ENTRY(editMeaningEntry),"*sửa thành công  ");
gtk_entry_set_text (GTK_ENTRY(editSearchEntry)," ");
}
static void deleteUpdateFunction( GtkButton   *button,GtkNotebook *notebook )
{
    char *e;

   e=(char*) gtk_entry_get_text (GTK_ENTRY (deleteSearchEntry));
      btdel(soundexTree,e);
      int i=btdel(root,e);
  if(i!=0) gtk_entry_set_text (GTK_ENTRY(deleteMeaningEntry),"*xóa ko thành công ");
  else gtk_entry_set_text (GTK_ENTRY(deleteMeaningEntry),"*xóa thành công ");
  gtk_entry_set_text (GTK_ENTRY(deleteSearchEntry)," ");

}

static void editTab( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;

    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 2);

}

/*static void addUpdate( GtkButton   *button,
                         GtkNotebook *notebook )
{
    char *e,*f;

   e=(char*) gtk_entry_get_text (GTK_ENTRY (addWordEntry));
      f=(char*) gtk_entry_get_text (GTK_ENTRY (addMeaningEntry));

int i=btins(root,e,f,sizeof(data));
  if(i==46) gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"*từ đã tồn tại");
  else if(i==52) gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"sorry,btree đầy");
  else if(i==0){
    gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"*Thêm thành công");
    char ma[5];
    SoundEx(ma,e,4,1);
    btins(soundexTree,e,ma,5*sizeof(char));
  }
  gtk_entry_set_text (GTK_ENTRY(addWordEntry)," ");
}*/
static void addUpdate( GtkButton   *button,
                         GtkNotebook *notebook )
{
    char *e,*f;

   e=(char*) gtk_entry_get_text (GTK_ENTRY (addWordEntry));
      f=(char*) gtk_entry_get_text (GTK_ENTRY (addMeaningEntry));

int i=btins(root,e,f,sizeof(data));
  if(i==46) gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"*từ đã tồn tại");
  else if(i==52) gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"sorry,btree đầy");
  else if(i==0){
    gtk_entry_set_text (GTK_ENTRY(addMeaningEntry),"*Thêm thành công");
    char ma[5];
    SoundEx(ma,e,4,1);
    btins(soundexTree,e,ma,5*sizeof(char));
  }
gtk_entry_set_text (GTK_ENTRY(addWordEntry)," ");
}

static void deleteTab( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;

    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 3);

    /* Need to refresh the widget --
     This forces the widget to redraw itself. */
    //gtk_widget_queue_draw (GTK_WIDGET (notebook));
}


static GtkWidget *xpm_label_box( gchar     *xpm_filename,
                                 gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* Create box for image and label */
    box = gtk_box_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file (xpm_filename);
    //gtk_widget_set_size_request(image,30,30);

    /* Create a label for the button */
    label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}
static GtkWidget *xpm_label_box2( gchar     *xpm_filename
                                 )
{
    GtkWidget *box;
    //GtkWidget *label;
    GtkWidget *image;

    /* Create box for image and label */
    box = gtk_box_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file (xpm_filename);
    //gtk_widget_set_size_request(image,30,30);

    /* Create a label for the button */
    //label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
//    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    //gtk_widget_show (label);

    return box;
}
