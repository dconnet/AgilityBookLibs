#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
 * Localization support for HTML Tidy.
 *
 *
 * This file is a localization file for HTML Tidy. It will have been machine
 * generated or created and/or edited by hand. Both are valid options, but
 * please help keep our localization efforts simple to maintain by maintaining
 * the structure of this file, and changing the check box below if you make
 * changes (so others know the file origin):
 *
 * [X] THIS FILE IS MACHINE GENERATED. It is a localization file for the
 *     language (and maybe region) "es". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_es.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_es.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-10-03 12:44:37
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_es(uint n) {
    /* Plural-Forms: nplurals=2; */
    return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_es = { whichPluralForm_es, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,          0, "es"
    },
    { TidyMakeClean,          0,        
        "Esta opci??n especifica si Tidy debe realizar la limpieza de alg??n legado etiquetas de "
        "presentaci??n (actualmente <code>&lt;i&gt;</code>, <code>&lt;b&gt;</code>, <code>&lt;center&gt;</"
        "code> cuando encerrados dentro de las etiquetas apropiadas en l??nea y <code>&lt;font&gt;</"
        "code>). Si se establece en <code>yes</code>, entonces etiquetas existentes ser??n reemplazados "
        "con CSS <code>&lt;style&gt;</code> y estructural markup seg??n corresponda. "
    },
    { TidyNCR,                0, "Esta opci??n especifica si Tidy debe permitir referencias de caracteres num??ricos. "   },
    { TEXT_GENERAL_INFO_PLEA, 0,        
        "\n"
        "??Le gustar??a ver Tidy en un espa??ol correcto? Por favor considere \n"
        "ayudarnos a localizar HTML Tidy. Para m??s detalles consulte \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
    },

#if SUPPORT_CONSOLE_APP
    { TC_TXT_HELP_LANG_1,     0,        
        "\n"
        "La opci??n -language (o -lang) indica el lenguaje Tidy debe \n"
        "utilizar para comunicar su salida. Tenga en cuenta que esto no es \n"
        "un servicio de traducci??n de documentos, y s??lo afecta a los mensajes \n"
        "que Tidy comunica a usted. \n"
        "\n"
        "Cuando se utiliza la l??nea de comandos el argumento -language debe \n"
        "utilizarse antes de cualquier argumento que dan lugar a la producci??n, \n"
        "de lo contrario Tidy producir?? la salida antes de que se conozca el \n"
        "idioma a utilizar. \n"
        "\n"
        "Adem??s de los c??digos de idioma est??ndar POSIX, Tidy es capaz de \n"
        "entender c??digos de idioma legados de Windows. Tenga en cuenta que \n"
        "este lista indica los c??digos Tidy entiende, y no indica que \n"
        "actualmente el idioma est?? instalado. \n"
        "\n"
        "La columna m??s a la derecha indica c??mo Tidy comprender?? el \n"
        "legado nombre de Windows.\n"
        "\n"
        "Tidy est?? utilizando la configuraci??n regional %s. \n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,     0,        
        "\n"
        "Los siguientes idiomas est??n instalados actualmente en Tidy. Tenga \n"
        "en cuenta que no hay garant??a de que est??n completos; s??lo quiere decir \n"
        "que un desarrollador u otro comenzaron a a??adir el idioma indicado. \n"
        "\n"
        "Localizaciones incompletas por defecto se usan \"en\" cuando sea \n"
        "necesario. ??Favor de informar los desarrolladores de estes casos! \n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,     0,        
        "\n"
        "Si Tidy es capaz de determinar la configuraci??n regional entonces \n"
        "Tidy utilizar?? el lenguaje de forma autom??tica de la configuraci??n \n"
        "regional. Por ejemplo los sistemas de tipo Unix utilizan los variables \n"
        "$LANG y/o $LC_ALL. Consulte a su documentaci??n del sistema para \n"
        "obtener m??s informaci??n.\n"
        "\n"
        "Tidy est?? utilizando la configuraci??n regional %s. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST, 0, NULL
    }

}};


#endif /* language_es_h */

