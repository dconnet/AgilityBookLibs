#ifndef language_pt_br_h
#define language_pt_br_h
/*
 * language_pt_br.h
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
 *     language (and maybe region) "pt_br". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_pt_br.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_pt_br.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-10-05 15:13:40
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_pt_br(uint n) {
    /* Plural-Forms: nplurals=2; */
    return (n > 1);
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_pt_br = { whichPluralForm_pt_br, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                                 0, "pt_br"
    },
    { TidyAccessibilityCheckLevel,                   0,        
        "Esta op????o especifica o n??vel de verifica????o de acessibilidade, se houver, "
        "que Tidy deve executar. <br/>N??vel <var>0 (Tidy Classic)</var> ?? equivalente "
        "?? verifica????o de acessibilidade do Tidy Classic.<br/> Para obter mais "
        "informa????es sobre a verifica????o de acessibilidade do Tidy, visite <a href=\""
        "http://www.html-tidy.org/accessibility/\"> P??gina de acessibilidade do "
        "Tidy</a>. "
    },
    { TidyAltText,                                   0,        
        "Esta op????o especifica o texto padr??o <code>alt=</code> que o Tidy usa para "
        "atributos <code>&lt;img&gt;</code> quando o atributo <code>alt=</code> est?? "
        "faltando. <br/>Use com cuidado, pois ?? sua responsabilidade tornar seus "
        "documentos acess??veis para pessoas que n??o conseguem ver as imagens. "
    },
    { TidyAnchorAsName,                              0,        
        "Esta op????o controla a exclus??o ou adi????o do atributo <code>name</code> em "
        "elementos onde ele pode servir como ??ncora. <br/>Se configurado para "
        "<var>yes</var>, um atributo <code>name</code>, se n??o j?? existir, ?? "
        "adicionado ao longo de um atributo <code>id</code> existente se o DTD o "
        "permitir. <br/>Se configurado para <var>no</var> qualquer atributo de nome "
        "existente ?? removido se um atributo <code>id</code> existir ou tenha sido "
        "adicionado. "
    },
    { TidyAsciiChars,                                0,        
        "Pode ser usado para modificar o comportamento da op????o <code>clean</code> "
        "quando configurado para <var>yes</var>. <br/>Se configurado para "
        "<var>yes</var> ao usar <code>clean</code>, <code>&amp;emdash;</code>, "
        "<code>&amp;rdquo;</code>, e outras entidades de caracteres nomeadas s??o "
        "rebaixadas para os equivalentes ASCII mais pr??ximos. "
    },
    { TidyBlockTags,                                 0,        
        "Esta op????o especifica novas tags de n??vel de bloco. Esta op????o possui uma "
        "lista separada por v??rgulas ou espa??o de nomes de tags. <br/>A menos que "
        "voc?? declare novas tags, o Tidy se recusar?? a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Note que voc?? n??o "
        "pode alterar o modelo de conte??do para elementos como "
        "<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, <code>&lt;ol&gt;</code> "
        "e <code>&lt;dl&gt;</code>. <br/>Esta op????o ?? ignorada no modo XML. "
    },
    { TidyBodyOnly,                                  0,        
        "Esta op????o especifica se o Tidy deve imprimir apenas o conte??do da tag body "
        "como um fragmento HTML. <br/>Se configurado para <var>auto</var>, isso ?? "
        "realizado somente se a tag body tiver sido inferida. <br/>??til para "
        "incorporar p??ginas inteiras existentes como uma por????o de outra p??gina. <br/>"
        "Esta op????o n??o tem efeito se a sa??da XML for solicitada. "
    },
    { TidyBreakBeforeBR,                             0,        
        "Esta op????o especifica se o Tidy deve emitir uma quebra de linha antes de "
        "cada elemento <code>&lt;br&gt;</code>. "
    },
    { TidyCharEncoding,                              0,        
        "Esta op????o especifica a codifica????o de caracteres que o Tidy usa tanto para "
        "a entrada como para a sa??da. <br/>Para <var>ascii</var>, o Tidy aceitar?? "
        "valores de caracteres Latin-1 (ISO-8859-1), mas usar?? entidades para todos "
        "os caracteres cujo valor seja &gt;127. <br/>Para <var>raw</var>, o Tidy "
        "emitir?? valores acima de 127 sem traduzi-los em entidades. <br/>Para "
        "<var>latin1</var>, os caracteres acima de 255 ser??o escritos como entidades. "
        "<br/>Para <var>utf8</var>, Tidy presume que tanto a entrada como a sa??da s??o "
        "codificadas como UTF-8. <br/>Voc?? pode usar <var>iso2022</var> para arquivos "
        "codificados usando a fam??lia de codifica????es ISO-2022, p.ex. ISO-2022-JP. "
        "<br/> Para <var>mac</var> e <var>win1252</var>, o Tidy aceitar?? valores de "
        "caracteres espec??ficos do fornecedor, mas usar?? entidades para todos os "
        "caracteres cujo valor seja &gt;127. <br/>Para codifica????es sem suporte, use "
        "um utilit??rio externo para converter de e para UTF-8. "
    },
    { TidyCoerceEndTags,                             0,        
        "Esta op????o especifica se o Tidy deve coagir uma tag de in??cio em uma tag de "
        "fim nos casos em que parece que uma tag de fim provavelmente foi projetada; "
        "por exemplo, dado <br/><code>&lt;span&gt;foo &lt;b&gt;bar&lt;b&gt; "
        "baz&lt;/span&gt;</code>, <br/>Tidy vai emitir <br/><code>&lt;span&gt;foo "
        "&lt;b&gt;bar&lt;/b&gt; baz&lt;/span&gt;</code> "
    },
    { TidyCSSPrefix,                                 0,        
        "Esta op????o especifica o prefixo que o Tidy usa para regras de estilo. <br/>Por padr??o, <var>c</"
        "var> ser?? usado. "
    },
    { TidyDecorateInferredUL,                        0,        
        "Esta op????o especifica se o Tidy deve decorar elementos inferidos "
        "<code>&lt;ul&gt;</code> com algumas marca????es CSS para evitar recuo para a "
        "direita. "
    },
    { TidyDoctype,                                   0,        
        "Esta op????o especifica a declara????o DOCTYPE gerada pelo Tidy. <br/>Se "
        "configurado para <var>omit</var>, a sa??da n??o conter?? uma declara????o "
        "DOCTYPE. Note que isso tamb??m implica que <code>numeric-entity</code> esteja "
        "definido para <var>yes</var>. <br/>Se configurado para <var>html5</var>, o "
        "DOCTYPE ?? configurado para <code>&lt;!DOCTYPE html&gt;</code>. <br/>Se "
        "configurado para <var>auto</var> (o padr??o), Tidy usar?? um palpite educado "
        "com base no conte??do do documento. <br/>Se configurado para <var>strict</var>"
        ", o Tidy configurar?? o DOCTYPE para o DTD estrito HTML4 ou XHTML1. <br/>Se "
        "configurado para <var>loose</var>, o DOCTYPE ?? definido como o DTD loose "
        "(transicional) HTML4 ou XHTML1. <br/>Alternativamente, voc?? pode fornecer "
        "uma string para o identificador p??blico formal (FPI). <br/>Por exemplo: "
        "<br/><code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code><br/>Se voc?? "
        "especificar o FPI para um documento XHTML, o Tidy ir?? definir o "
        "identificador do sistema em uma string vazia. Para um documento HTML, a Tidy "
        "adiciona um identificador de sistema somente se um j?? estivesse presente "
        "para preservar o modo de processamento de alguns navegadores. Tidy deixa o "
        "DOCTYPE para documentos gen??ricos XML inalterados. <br/>Esta op????o n??o "
        "oferece uma valida????o da conformidade do documento. "
    },
    { TidyDropEmptyElems,                            0, "Esta op????o especifica se Tidy deve descartar elementos vazios. "                                 },
    { TidyDropEmptyParas,                            0, "Esta op????o especifica se Tidy deve descartar par??grafos vazios. "                                },
    { TidyDropPropAttrs,                             0,        
        "Esta op????o especifica se o Tidy deve remover os atributos de propriedade, "
        "como os atributos de liga????o de dados da Microsoft. Al??m disso, os atributos "
        "que n??o s??o permitidos na vers??o de sa??da do HTML ser??o descartados se "
        "usados com <code>strict-tags-attributes</code>. "
    },
    { TidyDuplicateAttrs,                            0,        
        "Esta op????o especifica se o Tidy deve manter o primeiro ou ??ltimo atributo, "
        "se um atributo estiver repetido, p.ex. possui dois atributos "
        "<code>align</code>. "
    },
    { TidyEmacs,                                     0,        
        "Esta op????o especifica se o Tidy deve alterar o formato para relatar erros e "
        "avisos para um formato que ?? analisado mais facilmente pelo GNU Emacs. "
    },
    { TidyEmptyTags,                                 0,        
        "Esta op????o especifica novas tags em-linha vazias. Esta op????o possui uma "
        "lista separada por espa??o ou v??rgulas de nomes de tags. <br/>A menos que "
        "voc?? declare novas tags, o Tidy se recusar?? a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Lembre-se de declarar "
        "tags vazias como em linha ou bloqueio. <br/>Esta op????o ?? ignorada no modo "
        "XML. "
    },
    { TidyEncloseBlockText,                          0,        
        "Esta op????o especifica se Tidy deve inserir um elemento <code>&lt;p&gt;</code>"
        " para incluir qualquer texto que encontre em qualquer elemento que permita o "
        "conte??do misto para HTML transicional mas n??o HTML estrito. "
    },
    { TidyEncloseBodyText,                           0,        
        "Esta op????o especifica se o Tidy deve incluir qualquer texto encontrado no "
        "elemento do corpo dentro de um elemento <code>&lt;p&gt;</code>. <br/>Isso ?? "
        "??til quando voc?? deseja usar o HTML existente e us??-lo com uma folha de "
        "estilo. "
    },
    { TidyErrFile,                                   0,        
        "Esta op????o especifica o arquivo de erro que o Tidy usa para erros e avisos. "
        "Normalmente, erros e avisos s??o emitidos para <code>stderr</code>. "
    },
    { TidyEscapeCdata,                               0,        
        "Esta op????o especifica se o Tidy deve converter se????es "
        "<code>&lt;![CDATA[]]&gt;</code> em texto normal. "
    },
    { TidyEscapeScripts,                             0,        
        "Esta op????o faz com que itens que se parecem com tags de fechamento, como <code>&lt;/g</code> "
        "sejam escapadas para <code>&lt;\\/g</code>. Defina esta op????o para <var>no</var> se voc?? n??o "
        "deseja isso."
    },
    { TidyFixBackslash,                              0,        
        "Esta op????o especifica se o Tidy deve substituir caracteres de barra "
        "invertida <code>\\</code> em URLs com barras <code>/</code>. "
    },
    { TidyFixComments,                               0,        
        "Esta op????o especifica se Tidy deve substituir h??fenes inesperados com "
        "caracteres <code>=</code> quando se trata de h??fenes adjacentes. <br/>O "
        "padr??o ?? <var>yes</var>. <br/>Esta op????o ?? fornecida para usu??rios do Cold "
        "Fusion que usam a sintaxe do coment??rio: <code>&lt;!--- ---&gt;</code>. "
    },
    { TidyFixUri,                                    0,        
        "Esta op????o especifica se o Tidy deve verificar valores de atributos que "
        "carregam URIs para caracteres ilegais e, se tal for encontrado, escapa-os "
        "conforme o HTML4 recomenda. "
    },
    { TidyForceOutput,                               0,        
        "Esta op????o especifica se o Tidy deve produzir sa??da, mesmo se forem "
        "encontrados erros. <br/>Use esta op????o com cuidado; Se o Tidy relatar um "
        "erro, significa que o Tidy n??o conseguiu corrigir o erro (ou n??o sabe como), "
        "ent??o a sa??da resultante pode n??o refletir sua inten????o. "
    },
    { TidyGDocClean,                                 0,        
        "Esta op????o especifica se o Tidy deve habilitar comportamento espec??fico para "
        "limpeza de HTML exportado do Google Docs. "
    },
    { TidyHideComments,                              0, "Esta op????o especifica se Tidy deve imprimir os coment??rios. "                                    },
    { TidyHtmlOut,                                   0,        
        "Esta op????o especifica se o Tidy deve gerar uma impress??o amig??vel, "
        "escrevendo como HTML. "
    },
    { TidyInCharEncoding,                            0,        
        "Esta op????o especifica a codifica????o de caracteres que o Tidy usa para a "
        "entrada. Veja <code>char-encoding</code> para mais informa????es. "
    },
    { TidyIndentAttributes,                          0,        
        "Esta op????o especifica se o Tidy deve come??ar cada atributo em uma nova "
        "linha. "
    },
    { TidyIndentCdata,                               0,        
        "Esta op????o especifica se o Tidy deve aplicar recuo nas se????es "
        "<code>&lt;![CDATA[]]&gt;</code>. "
    },
    { TidyIndentContent,                             0,        
        "Esta op????o especifica se Tidy deve aplicar recuo nas tags de n??vel de bloco. "
        "<br/>Se configurado para <var>auto</var>, Tidy decidir?? se aplica ou n??o "
        "recuo no conte??do das tags, como <code>&lt;title&gt;</code>, "
        "<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, "
        "<code>&lt;td&gt;</code> ou <code>&lt;p&gt;</code> com base no conte??do, "
        "incluindo um elemento de n??vel de bloco. <br/>Configurar <code>indent</code> "
        "para <var>yes</var> pode expor erros de layout em alguns navegadores. <br/>"
        "Use a op????o <code>indent-spaces</code> para controlar o n??mero de espa??os ou "
        "tabula????es de sa??da por n??vel de recuo e <code>indent-with-tabs</code> para "
        "especificar se espa??os ou tabula????es s??o usados. "
    },
    { TidyIndentSpaces,                              0,        
        "Esta op????o especifica o n??mero de espa??os ou guias que o Tidy usa para "
        "recuar o conte??do quando <code>indent</code> est?? habilitado. <br/>Note que "
        "o valor padr??o para esta op????o depende do valor de <code>indent-with-"
        "tabs</code> (veja tamb??m). "
    },
    { TidyInlineTags,                                0,        
        "Esta op????o especifica novas tags em-linha n??o vazias. Esta op????o possui uma "
        "lista separada por espa??o ou v??rgulas de nomes de tags. <br/>A menos que "
        "voc?? declare novas tags, o Tidy se recusar?? a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Esta op????o ?? ignorada "
        "no modo XML. "
    },
    { TidyJoinClasses,                               0,        
        "Esta op????o especifica se o Tidy deve combinar os nomes das classes para "
        "gerar um nome de classe ??nico e novo se v??rias atribui????es de classe forem "
        "detectadas em um elemento. "
    },
    { TidyJoinStyles,                                0,        
        "Esta op????o especifica se o Tidy deve combinar os estilos para gerar um "
        "estilo ??nico e novo se v??rios valores de estilo forem detectados em um "
        "elemento. "
    },
    { TidyKeepFileTimes,                             0,        
        "Esta op????o especifica se o Tidy deve manter o tempo de modifica????o original "
        "dos arquivos que o Tidy modifica no local. <br/>Configurar a op????o para "
        "<var>yes</var> permite arrumar arquivos sem alterar a data de modifica????o do "
        "arquivo, o que pode ser ??til com determinadas ferramentas que usam a data de "
        "modifica????o para coisas como a implanta????o autom??tica do servidor. <br/>Note "
        "que n??o h?? suporte a este recurso em algumas plataformas. "
    },
    { TidyLiteralAttribs,                            0,        
        "Esta op????o especifica como o Tidy lida com caracteres de espa??o em branco "
        "dentro de valores de atributos. <br/>Se o valor for <var>no</var>, Tidy "
        "normaliza os valores dos atributos substituindo qualquer nova linha ou "
        "tabula????o por um ??nico espa??o, al??m de substituir qualquer espa??o cont??guo "
        "em espa??o ??nico. <br/>Para for??ar o Tidy a preservar os valores literais "
        "originais de todos os atributos e garantir que os espa??os em branco dentro "
        "dos valores de atributo sejam passados inalterados atrav??s, defina esta "
        "op????o como <var>yes</var>. "
    },
    { TidyLogicalEmphasis,                           0,        
        "Esta op????o especifica se o Tidy deve substitui qualquer ocorr??ncia de "
        "<code>&lt;i&gt;</code> com <code>&lt;em&gt;</code> e qualquer ocorr??ncia de "
        "<code>&lt;b&gt;</code> com <code>&lt;strong&gt;</code>. Quaisquer atributos "
        "s??o preservados inalterados. <br/>Esta op????o pode ser definida "
        "independentemente da op????o <code>clean</code>. "
    },
    { TidyLowerLiterals,                             0,        
        "Esta op????o especifica se o Tidy deve converter o valor de um atributo que "
        "leva uma lista de valores predefinidos para min??sculas. <br/>Isto ?? "
        "necess??rio para documentos XHTML. "
    },
    { TidyMakeBare,                                  0,        
        "Esta op????o especifica se o Tidy deve retirar o HTML espec??fico da Microsoft "
        "de documentos do Word 2000 e exibir espa??os em vez de espa??os r??gidos (nbsp) "
        "nos quais eles existam na entrada. "
    },
    { TidyMakeClean,                                 0,        
        "Esta op????o especifica se o Tidy deve executar a limpeza de algumas tags de "
        "apresenta????o legadas (atualmente <code>&lt;i&gt;</code>, "
        "<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> quando inclu??das nas "
        "tags em-linha apropriadas e <code>&lt;font&gt;</code>). Se configurado para "
        "<var>yes</var>, as tags legadas ser??o substitu??das por tags CSS "
        "<code>&lt;style&gt;</code> e marca????o estrutural conforme apropriado. "
    },
    { TidyMark,                                      0,        
        "Esta op????o especifica se o Tidy deve adicionar um elemento <code>meta</code> "
        "ao cabe??alho do documento para indicar que o documento foi arrumado. <br/>"
        "Tidy n??o adicionar?? um elemento meta se um j?? estiver presente. "
    },
    { TidyMergeDivs,                                 0,        
        "Esta op????o pode ser usada para modificar o comportamento de "
        "<code>clean</code> quando configurado para <var>yes</var>. <br/>Esta op????o "
        "especifica se o Tidy deve mesclar <code>&lt;div&gt;</code> aninhados, como "
        "<code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. <br/>Se "
        "configurado para <var>auto</var>, os atributos do <code>&lt;div&gt;</code> "
        "internos s??o movidos para o externo. <code>&lt;div&gt;</code> aninhados com "
        "os atributos <code>id</code> <em>n??o</em> s??o mesclados. <br/>Se configurado "
        "para <var>yes</var>, os atributos de <code>&lt;div&gt;</code> interno s??o "
        "descartados com a exce????o de <code>class</code> e <code>style</code>. "
    },
    { TidyMergeEmphasis,                             0,        
        "Esta op????o especifica se o Tidy deve mesclar elementos <code>&lt;b&gt;</code>"
        " e <code>&lt;i&gt;</code> aninhados; por exemplo, para o caso de "
        "<br/><code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\""
        "&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, <br/>Tidy vai emitir <code>&lt;b "
        "class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
    },
    { TidyMergeSpans,                                0,        
        "Esta op????o pode ser usada para modificar o comportamento de "
        "<code>clean</code> quando configurado para <var>yes</var>. <br/>Esta op????o "
        "especifica se o Tidy deve mesclar <code>&lt;span&gt;</code> aninhados como "
        "<code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. <br/>O "
        "algoritmo ?? id??ntico ??quele usado por <code>merge-divs</code>. "
    },
    { TidyNCR,                                       0,        
        "Esta op????o especifica se o Tidy deve permitir refer??ncias de caracteres "
        "num??ricos. "
    },
    { TidyNewline,                                   0,        
        "O padr??o ?? apropriado para a plataforma atual. <br/>Geralmente, CRLF no PC-"
        "DOS, Windows e OS/2; CR no Mac OS Cl??ssico; e LF nos demais (Linux, Mac OS X "
        "e Unix). "
    },
    { TidyNumEntities,                               0,        
        "Esta op????o especifica se o Tidy deve produzir entidades diferentes das "
        "entidades HTML integradas (<code>&amp;amp;</code>, <code>&amp;lt;</code>, "
        "<code>&amp;gt;</code> e <code>&amp;quot;</code>) no formul??rio num??rico em "
        "vez do formul??rio nomeado. <br/>Somente s??o usadas entidades compat??veis com "
        "a declara????o DOCTYPE gerada. <br/>As entidades que podem ser representadas "
        "na codifica????o de sa??da s??o traduzidas correspondentemente. "
    },
    { TidyOmitOptionalTags,                          0,        
        "Esta op????o especifica se o Tidy deve omitir tags de in??cio e de fim "
        "opcionais ao gerar sa??da. <br/>Configurar essa op????o causa todas as tags "
        "para os elementos <code>&lt;html&gt;</code>, <code>&lt;head&gt;</code> e "
        "<code>&lt;body&gt;</code> serem omitidos da sa??da, assim como tags de sa??da "
        "como <code>&lt;/p&gt;</code>, <code>&lt;/li&gt;</code>, "
        "<code>&lt;/dt&gt;</code>, <code>&lt;/dd&gt;</code>, "
        "<code>&lt;/option&gt;</code>, <code>&lt;/tr&gt;</code>, "
        "<code>&lt;/td&gt;</code> e <code>&lt;/th&gt;</code>. <br/>Essa op????o ?? "
        "ignorada para sa??da XML. "
    },
    { TidyOutCharEncoding,                           0,        
        "Esta op????o especifica a codifica????o de caracteres que o Tidy usa para a sa??da. <br/>Note que "
        "isso s?? pode ser diferente de <code>input-encoding</code> para codifica????es latinas "
        "(<var>ascii</var>, <var>latin0</var>, <var>latin1</var>, <var>mac</var>, <var>win1252</var>, "
        "<var>ibm858</var>). <br/>Veja <code>char-encoding</code> para mais informa????es"
    },
    { TidyOutFile,                                   0,        
        "Essa op????o especifica o arquivo de sa??da que o Tidy usa para marca????o. "
        "Normalmente, a marca????o ?? escrita para <code>stdout</code>. "
    },
    { TidyOutputBOM,                                 0,        
        "Esta op????o especifica se o Tidy deve escrever um caractere Unicode de marca "
        "de ordem de byte (BOM, tamb??m conhecido como Zero Width No Break Break, tem "
        "valor de U+FEFF) no in??cio da sa??da, e aplica-se apenas a codifica????es de "
        "sa??da UTF-8 e UTF-16. <br/>Se configurado para <var>auto</var>, esta op????o "
        "faz com que Tidy escreva um BOM para a sa??da somente se um BOM estiver "
        "presente no in??cio da entrada. <br/>Um BOM est?? sempre escrita para sa??da "
        "XML/XHTML usando codifica????es de sa??da UTF-16. "
    },
    { TidyPPrintTabs,                                0,        
        "Esta op????o especifica se o Tidy deve aplicar recuo com tabula????es em vez de "
        "espa??os, presumindo que <code>indent</code> seja <var>yes</var>. <br/>Defina-"
        "o para <var>yes</var> para recuar usando tabula????es em vez dos espa??os "
        "padr??o. <br/>Use a op????o <code>indent-spaces</code> para controlar o n??mero "
        "de sa??das de tabula????o por n??vel de recuo. Note que quando <code>indent-with-"
        "tabs</code> est?? habilitado, o valor padr??o de <code>indent-spaces</code> ?? "
        "reiniciado para <var>1</var>. <br/>Note que <code>tab-size</code> controla a "
        "convers??o de tabula????es de entrada em espa??os. Coloque-o em zero para reter "
        "as tabula????es de entrada. "
    },
    { TidyPreserveEntities,                          0,        
        "Esta op????o especifica se o Tidy deve preservar entidades bem-formadas como "
        "localizado na entrada. "
    },
    { TidyPreTags,                                   0,        
        "Esta op????o especifica novas tags que devem ser processadas exatamente da "
        "mesma forma que o elemento <code>&lt;pre&gt;</code> de HTML. Esta op????o "
        "possui uma lista separada por v??rgulas ou espa??os de nomes de tag. <br/>A "
        "menos que voc?? declare novas tags, o Tidy se recusar?? a gerar um arquivo "
        "arrumado se a entrada incluir tags anteriormente desconhecidas. <br/>Note "
        "que voc?? ainda n??o pode adicionar novos elementos CDATA. <br/>Esta op????o ?? "
        "ignorada no modo XML. "
    },
    { TidyPunctWrap,                                 0,        
        "Essa op????o especifica se o Tidy deve quebrar linha ap??s alguns Unicode ou "
        "caracteres de pontua????o chineses. "
    },
    { TidyQuiet,                                     0,        
        "Essa op????o especifica se o Tidy deve emitir o resumo dos n??meros de erros e "
        "avisos, ou as mensagens de boas-vidas ou informacionais. "
    },
    { TidyQuoteAmpersand,                            0,        
        "Essa op????o especifica se o Tidy deve emitir caracteres <code>&amp;</code> "
        "sem adornos como <code>&amp;amp;</code>. "
    },
    { TidyQuoteMarks,                                0,        
        "Esta op????o especifica se o Tidy deve enviar caracteres <code>&quot;</code> "
        "como <code>&quot;</code> como ?? preferido por alguns ambientes de edi????o. "
        "<br/>O caractere do ap??strofe <code>'</code> ?? escrito como "
        "<code>&amp;#39;</code> porque muitos navegadores web ainda n??o oferecem "
        "suporte a <code>&amp;apos;</code>. "
    },
    { TidyQuoteNbsp,                                 0,        
        "Esta op????o especifica se o Tidy deve produzir caracteres de espa??o r??gido "
        "como entidades, em vez de como o caractere Unicode de valor 160 (decimal). "
    },
    { TidyReplaceColor,                              0,        
        "Esta op????o especifica se o Tidy deve substituir os valores num??ricos nos atributos de cor com "
        "nomes de cor HTML/XHTML onde definido, p.ex. substituir <code>#ffffff</code> com <code>white</"
        "code>. "
    },
    { TidyShowErrors,                                0,        
        "Esta op????o especifica o n??mero que o Tidy usa para determinar se outros "
        "erros devem ser exibidos. Se configurado para <var>0</var>, nenhum erro ser?? "
        "mostrado. "
    },
    { TidyShowInfo,                                  0,        
        "Esta op????o especifica se o Tidy deve exibir mensagens de n??vel "
        "informacional. "
    },
    { TidyShowMarkup,                                0,        
        "Esta op????o especifica se o Tidy deve gerar uma vers??o de impress??o amig??vel "
        "da marca????o. Note que o Tidy n??o gerar?? uma vers??o de impress??o amig??vel se "
        "encontrar erros significativos (veja <code>force-output</code>). "
    },
    { TidyShowWarnings,                              0,        
        "Esta op????o especifica se o Tidy deve suprimir avisos. Isso pode ser ??til "
        "quando alguns erros est??o ocultos em uma agita????o de avisos. "
    },
    { TidySkipNested,                                0,        
        "Esta op????o especifica que o Tidy deve pular tags aninhadas ao analisar "
        "script e dados de estilo. "
    },
    { TidySortAttributes,                            0,        
        "Esta op????o especifica que o Tidy deve ordenar atributos dentro de um "
        "elemento usando o algoritmo de ordena????o especificado. Se configurado para "
        "<var>alpha</var>, o algoritmo ?? uma ordena????o alfab??tica ascendente. "
    },
    { TidyStrictTagsAttr,                            0,        
        "Esta op????o garante que tags e atributos sejam aplic??veis ?? vers??o do HTML "
        "que o Tidy emite. Quando definido para <var>yes</var> e o tipo de documento "
        "de sa??da ?? um doctype estrito, ent??o o Tidy informar?? os erros. Se o tipo de "
        "documento de sa??da for um tipo de documento loose ou transicional, o Tidy "
        "informar?? os avisos. <br/>Al??m disso, se <code>drop-proprietary-"
        "attributes</code> estiver habilitado, os atributos n??o aplic??veis tamb??m "
        "ser??o descartados. <br/>Quando configurado para <var>no</var>, essas "
        "verifica????es n??o s??o executadas. "
    },
    { TidyTabSize,                                   0,        
        "Esta op????o especifica o n??mero de colunas que o Tidy usa entre paradas de "
        "tabula????o sucessivas. Ela ?? usada para mapear tabula????es para espa??os ao ler "
        "a entrada. "
    },
    { TidyUpperCaseAttrs,                            0,        
        "Esta op????o especifica se o Tidy deve produzir nomes de atributo em "
        "mai??sculo. <br/>Quando configurado para <var>no</var>, os nomes dos "
        "atributos ser??o escritos em min??sculas. Especificar <var>yes</var> exibir?? "
        "nomes de atributos em mai??sculas e <var>preserve</var> pode ser usado para "
        "deixar nomes de atributos intactos. <br/>Ao usar a entrada XML, o "
        "maiusculiza????o original ?? sempre preservada. "
    },
    { TidyUpperCaseTags,                             0,        
        "Esta op????o especifica se o Tidy deve emitir nomes de tags em mai??sculo. <br/>"
        "O padr??o ?? <var>no</var>, o que resulta em nomes de tags min??sculos, exceto "
        "para entrada XML na qual a maiusculiza????o original ?? preservada. "
    },
    { TidyUseCustomTags,                             0,        
        "Esta op????o permite o uso de tags para elementos personalizados aut??nomos, "
        "p.ex. &lt;flag-icon&gt; com Tidy. As tags personalizadas s??o desativadas se "
        "esse valor for <var>no</var>. Outras configura????es - <var>blocklevel</var>, "
        "<var>empty</var>, <var>inline</var> e <var>pre</var> tratar??o <em>todas</em> "
        "as tags personalizadas detectadas em conformidade. <br/>O uso de <code>new-"
        "blocklevel-tags</code>, <code>new-empty-tags</code>, <code>new-inline-"
        "tags</code> ou <code>new-pre-tags</code> substituir?? o tratamento de tags "
        "personalizadas por esta op????o de configura????o. Isso pode ser ??til se voc?? "
        "tiver diferentes tipos de tags personalizadas. <br/>Quando habilitado, essas "
        "tags s??o determinadas durante o processamento do documento usando tags de "
        "abertura; As tags de fechamento de correspond??ncia ser??o reconhecidas de "
        "acordo, e as tags de fechamento desconhecidas ser??o descartadas. "
    },
    { TidyVertSpace,                                 0,        
        "Esta op????o especifica se o Tidy deve adicionar algumas linhas vazias extras para legibilidade. "
        "<br/>O padr??o ?? <var>no</var>. <br/>Se configurado para <var>auto</var>, Tidy vai eliminar "
        "quase todos os caracteres de nova linha."
    },
    { TidyWarnPropAttrs,                             0, "Essa op????o especifica se o Tidy deve avisar sobre atributos propriet??rios."                      },
    { TidyWord2000,                                  0,        
        "Esta op????o especifica se o Tidy deve se esfor??ar duro para tirar todas as "
        "coisas excedentes que o Microsoft Word 2000 insere quando voc?? salva os "
        "documentos do Word como \"p??ginas web\". N??o manipula imagens embutidas ou "
        "VML. <br/>Voc?? deve considerar usar o Word \"Salvar Como: P??gina da Web, "
        "Filtrada\". "
    },
    { TidyWrapAsp,                                   0,        
        "Essa op????o especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do ASP, que se parecem com: <code>&lt;% ... %&gt;</code>. "
    },
    { TidyWrapAttVals,                               0,        
        "Esta op????o especifica se Tidy deve incluir valores de atributos de linha, o "
        "que significa que, se o valor de um atributo faz com que uma linha exceda a "
        "largura especificada por <code>wrap</code>, Tidy ir?? adicionar uma ou mais "
        "quebras de linha ao valor, fazendo com que ele seja embrulhado em v??rias "
        "linhas. <br/>Note que esta op????o pode ser definida independentemente de <code"
        ">wrap-script-literals</code>. Por padr??o, o Tidy substitui qualquer nova "
        "linha ou tabula????o com um ??nico espa??o e substitui qualquer sequ??ncia de "
        "espa??os em branco com um ??nico espa??o. <br/>Para for??ar a Tidy a preservar "
        "os valores literais originais de todos os atributos e garantir que os "
        "caracteres de espa??o em branco nos valores de atributos sejam passados "
        "atrav??s de altera????es, configure <code>literal-attributes</code> para "
        "<var>yes</var>. "
    },
    { TidyWrapJste,                                  0,        
        "Essa op????o especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do JSTE, que se parecem com: <code>&lt;# ... #&gt;</code>. "
    },
    { TidyWrapLen,                                   0,        
        "Esta op????o especifica a margem direita que o Tidy usa para quebra de linha. "
        "<br/>Tidy tenta quebrar linhas para que n??o excedam esse comprimento. <br/>"
        "Defina <code>wrap</code> para <var>0</var> (zero) se desejar desativar a "
        "quebra de linha. "
    },
    { TidyWrapPhp,                                   0,        
        "Essa op????o especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do PHP, que se parecem com: <code>&lt;?php ... ?&gt;</code>. "
    },
    { TidyWrapScriptlets,                            0,        
        "Esta op????o especifica se Tidy deve efetuar quebra de linha em string "
        "literais que aparecem em atributos de script."
    },
    { TidyWrapSection,                               0,        
        "Essa op????o especifica se o Tidy deve efetuar quebra de linha de textos "
        "contidos em tags de se????o <code>&lt;![ ... ]&gt;</code>. "
    },
    { TidyWriteBack,                                 0,        
        "Esta op????o especifica se o Tidy deve escrever novamente a marca????o arrumada "
        "para o mesmo arquivo que l??. <br/> ?? aconselh??vel manter c??pias de arquivos "
        "importantes antes de orden??-los, como em ocasi??es raras, o resultado pode "
        "n??o ser o que voc?? espera. "
    },
    { TidyXhtmlOut,                                  0,        
        "Esta op????o especifica se o Tidy deve gerar uma impress??o amig??vel, "
        "escrevendo como HTML extens??vel. <br/>Esta op????o faz com que o Tidy "
        "configure o DOCTYPE e o espa??o de nomes padr??o conforme apropriado para "
        "XHTML e use o valor corrigido no resultado, independentemente de outras "
        "fontes. <br/> Para XHTML, as entidades podem ser escritas como entidades "
        "nomeadas ou num??ricas de acordo com a configura????o de <code>numeric-"
        "entities</code>. <br/>A maiusculiza????o original de tags e atributos ser?? "
        "preservada, independentemente de outras op????es. "
    },
    { TidyXmlDecl,                                   0,        
        "Esta op????o especifica se o Tidy deve adicionar a declara????o XML ao enviar "
        "XML ou XHTML. <br/>Note que, se a entrada j?? incluir uma declara????o "
        "<code>&lt;?xml ... ?&gt;</code>, esta op????o ser?? ignorada. <br/>Se a "
        "codifica????o para a sa??da for diferente de <var>ascii</var>, uma das "
        "codifica????es <var>utf*</var> ou de <var>raw</var>, ent??o a declara????o ?? "
        "sempre adicionado conforme exigido pelo padr??o XML. "
    },
    { TidyXmlOut,                                    0,        
        "Esta op????o especifica se o Tidy deve emitir impress??o amig??vel, escrevendo-o "
        "como XML bem formado. <br/>Todas as entidades n??o definidas no XML 1.0 ser??o "
        "escritas como entidades num??ricas para permitir que elas sejam analisadas "
        "por um analisador XML. <br/>A maiusculiza????o original de tags e atributos "
        "ser?? preservada, independentemente de outras op????es. "
    },
    { TidyXmlPIs,                                    0,        
        "Esta op????o especifica se o Tidy deve alterar a an??lise das instru????es de "
        "processamento para exigir <code>?&gt;</code> como o terminador, em vez de "
        "<code>&gt;</code>. <br/>Esta op????o ?? configurada automaticamente se a "
        "entrada for um XML. "
    },
    { TidyXmlSpace,                                  0,        
        "Esta op????o especifica se o Tidy deve adicionar <code>xml:space=\"preserve\"</code> para "
        "elementos tais como <code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> e <code>&lt;script&gt;"
        "</code> ao gerar o XML. <br/>Isso ?? necess??rio se o espa??o em branco em tais elementos deve ser "
        "analisado apropriadamente sem ter acesso ao DTD. "
    },
    { TidyXmlTags,                                   0,        
        "Esta op????o especifica se o Tidy deve usar o analisador XML em vez do "
        "analisador HTML de corre????o de erro. "
    },
    { TidyMetaCharset,                               0,        
        "Esta op????o, quando ativada, adiciona um elemento <code>&lt;meta&gt;</code> e "
        "define o atributo <code>charset</code> para a codifica????o do documento. "
        "Configure esta op????o para <var>yes</var> para habilit??-lo. "
    },
    { TidyShowMetaChange,                            0,        
        "Esta op????o habilita uma mensagem sempre que o Tidy alterar o atributo "
        "<code>content</code> de uma declara????o de meta conjunto de caracteres para "
        "coincidir com a codifica????o do documento. Defina esta op????o para "
        "<var>yes</var> para habilit??-lo. "
    },
    { TidyStyleTags,                                 0,        
        "Esta op????o especifica se o Tidy deve mover todas as tags de estilo para o "
        "cabe??alho do documento. "
    },
    { TidyWarning,                                   0, "Acesso: "                                                                                        },
    { TidyAccess,                                    0, "Acesso: "                                                                                        },
    { TidyError,                                     0, "Erro: "                                                                                          },
    { TidyBadDocument,                               0, "Documento: "                                                                                     },
    { TidyFatal,                                     0, "P??nico: "                                                                                        },
    { TidyDialogueSummary,                           0, "Resumo: "                                                                                        },
    { TidyDialogueInfo,                              0, "Informa????o: "                                                                                    },
    { TidyDialogueFootnote,                          0, "Nota de rodap??: "                                                                                },
    { LINE_COLUMN_STRING,                            0, "linha %d coluna %d - "                                                                           },
    { STRING_DISCARDING,                             0, "descartando"                                                                                     },
    { STRING_ERROR_COUNT_ERROR,                      0, "erro"                                                                                            },
    { STRING_ERROR_COUNT_ERROR,                      1, "erros"                                                                                           },
    { STRING_ERROR_COUNT_WARNING,                    0, "aviso"                                                                                           },
    { STRING_ERROR_COUNT_WARNING,                    1, "avisos"                                                                                          },
    { STRING_HELLO_ACCESS,                           0,        
        "\n"
        "Verifica????es de acessibilidade:\n"
    },
    { STRING_HTML_PROPRIETARY,                       0, "Propriet??rio HTML"                                                                               },
    { STRING_XML_DECLARATION,                        0, "declara????o XML"                                                                                  },
    { STRING_PLAIN_TEXT,                             0, "texto simples"                                                                                   },
    { STRING_REPLACING,                              0, "substituindo"                                                                                    },
    { STRING_SPECIFIED,                              0, "especificada"                                                                                    },
    { TIDYCUSTOMNO_STRING,                           0, "n??o"                                                                                             },
    { TIDYCUSTOMBLOCKLEVEL_STRING,                   0, "n??vel de bloco"                                                                                  },
    { TIDYCUSTOMEMPTY_STRING,                        0, "vazio"                                                                                           },
    { TIDYCUSTOMINLINE_STRING,                       0, "em-linha"                                                                                        },
    { TIDYCUSTOMPRE_STRING,                          0, "pr??"                                                                                             },
    { TEXT_HTML_T_ALGORITHM,                         0,        
        "\n"
        "      - Primeiro, pesquisa ?? esquerda da posi????o da c??lula para\n"
        "        localizar c??lulas de cabe??alho de linha.\n"
        "      - Ent??o, pesquisa para cima para localizar c??lulas de cabe??alho\n"
        "        de coluna.\n"
        "      - A pesquisa em uma dire????o dada interrompe quando a borda da\n"
        "        tabela ?? atingida ou quando uma c??lula de dados ?? localizada\n"
        "        ap??s uma c??lula de cabe??alho.\n"
        "      - Cabe??alhos de linha s??o inseridas em uma linha na ordem que\n"
        "        elas aparecem na tabela.\n"
        "      - Para tabelas esquerda-para-direita, cabe??alhos s??o inseridas\n"
        "        da esquerda para direita.\n"
        "      - Cabe??alhos de coluna s??o inseridas ap??s cabe??alhos de linha,\n"
        "        na ordem que elas aparecem na tabela, de cima para baixo.\n"
        "      - Se uma c??lula de cabe??alho tem atributo de cabe??alhos configurado,\n"
        "        ent??o os cabe??alhos referenciados por este atributo s??o inseridos\n"
        "        na lisa e a pesquisa interrompe para a dire????o atual.\n"
        "        c??lulas TD que configuram o atributo de eixo tamb??m s??o tratadas\n"
        "        com c??lulas de cabe??alho.\n"
    },
    { TEXT_VENDOR_CHARS,                             0,        
        "?? improv??vel que as codifica????es dependentes do sistema espec??ficas\n"
        "do fornecedor funcionem amplamente na World Wide Web; voc?? deve\n"
        "evitar o uso da codifica????o de caracteres %s; em vez disso,\n"
        "recomenda-se que voc?? use entidades nomeadas, p.ex. &trade;.\n"
    },
    { TEXT_SGML_CHARS,                               0,        
        "Os c??digos de caracteres 128 a 159 (U+0080 a U+009F)\n"
        "n??o s??o aceitos no HTML; mesmo se eles fossem, eles\n"
        "provavelmente seriam caracteres de controle n??o imprim??veis.\n"
        "Tidy presumiu que voc?? queria se referir a um caractere\n"
        "com o mesmo valor de bytes na codifica????o %s e substituiu\n"
        "aquela refer??ncia com o equivalente Unicode.\n"
    },
    { TEXT_INVALID_UTF8,                             0,        
        "Os c??digos de caracteres para UTF-8 devem estar dentro\n"
        "do intervalo: U+0000 a U+10FFFF. A defini????o de UTF-8\n"
        "no Anexo D do ISO/IEC 10646-1:2000 tamb??m permite para\n"
        "o uso de sequ??ncias de cinco e seis bytes para codificar\n"
        "caracteres que est??o fora do intervalo do conjunto de\n"
        "caracteres do Unicode; aquelas sequ??ncias de cinco e\n"
        "seis bytes s??o ilegais para o uso de UTF-8 como uma\n"
        "transforma????o de caracteres Unicode. ISO/IEC 10646 n??o\n"
        "permite mapeamento de substitutos n??o pareados, nem\n"
        "U+FFFE e U+FFFF (mas permite outros n??o caracteres).\n"
        "Para mais informa????es, veja http://www.unicode.org/ e\n"
        "http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_UTF16,                            0,        
        "Os c??digos de caracteres para UTF-16 devem estar dentro\n"
        "do intervalo: U+0000 a U+10FFFF. A defini????o de UTF-16\n"
        "no Anexo C da ISO/IEC 10646-1:2000 n??o permite o mapeamento\n"
        "de substitutos n??o pareados. Para mais informa????es,\n"
        "por favor veja http://www.unicode.org/ e\n"
        "http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_URI,                              0,        
        "URIs devem ser devidamente escapadas, elas n??o devem\n"
        "conter caracteres n??o elaborados abaixo de U+0021,\n"
        "incluindo o caractere de espa??o e n??o acima de U+007E.\n"
        "Tidy escapa a URI para voc?? conforme recomendado pelo\n"
        "HTML 4.01 se????o B.2.1 e XML 1.0 se????o 4.2.2. Alguns\n"
        "agentes de usu??rios usam outro algoritmo para escapar\n"
        "tais URIs e alguns scripts de servidor dependem disso.\n"
        "Se voc?? quiser depender disso, voc?? deve escapar a URI\n"
        "por conta pr??pria. Para mais informa????es, consulte\n"
        "http://www.w3.org/International/O-URL-and-ident.html\n"
    },
    { TEXT_BAD_FORM,                                 0,        
        "Talvez seja necess??rio mover uma ou ambas as tags <form>\n"
        "e </form>. Os elementos HTML devem estar adequadamente\n"
        "aninhados e os elementos de formul??rio n??o s??o uma exce????o.\n"
        "Por exemplo, voc?? n??o deve colocar o <form> em uma c??lula\n"
        "de tabela e </form> em outra. Se o <form> for colocado\n"
        "antes de uma tabela, o </form> n??o pode ser colocado dentro\n"
        "da tabela! Note que um formul??rio n??o pode ser aninhado\n"
        "dentro de outro!\n"
    },
    { TEXT_BAD_MAIN,                                 0,        
        "Apenas um elemento <main> ?? permitido em um documento.\n"
        "Elementos <main> subsequentes foram descartados, o que\n"
        "pode tornar o documento inv??lido.\n"
    },
    { TEXT_M_SUMMARY,                                0,        
        "O atributo de resumo da tabela deve ser usado para\n"
        "descrever a estrutura da tabela. ?? muito ??til para\n"
        "pessoas que usam navegadores n??o visuais. Os atributos\n"
        "de escopo e cabe??alho para c??lulas de tabela s??o\n"
        "??teis para especificar quais cabe??alhos se aplicam\n"
        "a cada c??lula de tabela, permitindo que navegadores\n"
        "n??o visuais forne??am um contexto significativo para\n"
        "cada c??lula.\n"
    },
    { TEXT_M_IMAGE_ALT,                              0,        
        "O atributo alt deve ser usado para dar uma breve descri????o\n"
        "de uma imagem; descri????es mais longas devem ser fornecidas\n"
        "com o atributo longdesc que leva uma URL vinculada ??\n"
        "descri????o. Essas medidas s??o necess??rias para pessoas que\n"
        "usam navegadores n??o-gr??ficos.\n"
    },
    { TEXT_M_IMAGE_MAP,                              0,        
        "Use os mapas de imagens do lado do cliente de prefer??ncia\n"
        "aos mapas de imagens do lado do servidor, pois estes s??o\n"
        "inacess??veis para pessoas que usam navegadores n??o gr??ficos.\n"
        "Al??m disso, os mapas do lado do cliente s??o mais f??ceis\n"
        "de configurar e fornecer feedback imediato aos usu??rios.\n"
    },
    { TEXT_M_LINK_ALT,                               0,        
        "Para links de hipertexto definidos usando um mapa de imagem\n"
        "do lado do cliente, voc?? precisa usar o atributo alt para\n"
        "fornecer uma descri????o textual do link para pessoas que usam\n"
        "navegadores n??o gr??ficos.\n"
    },
    { TEXT_USING_FRAMES,                             0,        
        "P??ginas desenhadas usando quadros apresentam problemas\n"
        "para pessoas que s??o cegas ou que usam um navegador que\n"
        "n??o oferece suporte a quadros. Uma p??gina baseada em\n"
        "quadros deve sempre incluir um layout alternativo dentro\n"
        "de um elemento NOFRAMES.\n"
    },
    { TEXT_ACCESS_ADVICE1,                           0,        
        "Para mais conselhos sobre como tornar suas p??ginas\n"
        "acess??veis, veja http://www.w3.org/WAI/GL."
    },
    { TEXT_ACCESS_ADVICE2,                           0,        
        "Para mais conselhos sobre como tornar suas p??ginas\n"
        "acess??veis, veja http://www.w3.org/WAI/GL e\n"
        "http://www.html-tidy.org/accessibility/."
    },
    { TEXT_USING_LAYER,                              0,        
        "O mecanismo de posicionamento do Cascading Style\n"
        "Sheets (CSS) ?? recomendado em prefer??ncia ao\n"
        "elemento propriet??rio <LAYER> devido ao suporte\n"
        "de fornecedor limitado a LAYER.\n"
    },
    { TEXT_USING_SPACER,                             0,        
        "?? recomend??vel usar CSS para controlar o espa??o em\n"
        "branco (p.ex., para recuo, margens e espa??amento\n"
        "entre linhas). O elemento propriet??rio <SPACER>\n"
        "possui suporte limitado para fornecedores.\n"
    },
    { TEXT_USING_FONT,                               0,        
        "?? recomend??vel usar o CSS para especificar a fonte e\n"
        "as propriedades, como seu tamanho e cor. Isso reduzir??\n"
        "o tamanho dos arquivos HTML e facilitando a manuten????o\n"
        "em compara????o com o uso de elementos <FONT>.\n"
    },
    { TEXT_USING_NOBR,                               0,        
        "?? recomend??vel usar CSS para controlar a quebra de linha.\n"
        "Use \"white-space: nowrap\" para inibir a quebra em vez\n"
        "de inserir <NOBR>...</NOBR> na marca????o.\n"
    },
    { TEXT_USING_BODY,                               0, "?? recomend??vel usar CSS para especificar cores de p??gina e link"                                 },
    { STRING_CONTENT_LOOKS,                          0, "O conte??do do documento se parece com %s"                                                        },
    { STRING_DOCTYPE_GIVEN,                          0, "Doctype dado ?? \"%s\""                                                                           },
    { STRING_ERROR_COUNT,                            0, "Tidy encontrou %u %s e %u %s!\n"                                                                 },
    { STRING_NEEDS_INTERVENTION,                     0,        
        "Esse documento possui erros que devem ser corrigidos\n"
        "antes de usar HTML Tidy para gerar uma vers??o arrumada.\n"
    },
    { STRING_NO_ERRORS,                              0, "Nenhum aviso ou erro foi localizado.\n"                                                          },
    { STRING_NO_SYSID,                               0, "Nenhum identificado de sistema no doctype emitido"                                               },
    { STRING_NOT_ALL_SHOWN,                          0, "Tidy encontrou %u %s e %u %s! Nem todos avisos/erros foram mostrados.\n"                         },
    { TEXT_GENERAL_INFO,                             0,        
        "Sobre o HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Relat??rios de erro e coment??rios: https://github.com/htacg/tidy-html5/"
        "issues\n"
        "Lista de discuss??o: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Especifica????o HTML mais recente: http://dev.w3.org/html5/spec-author-view/\n"
        "Valide seus documentos HTML: http://validator.w3.org/nu/\n"
        "Incentive sua empresa a se juntar ?? W3C: http://www.w3.org/Consortium\n"
    },
    { TEXT_GENERAL_INFO_PLEA,                        0,        
        "Voc?? fala um idioma diferente do portugu??s brasileiro, ou uma variante \n"
        "diferente do portugu??s? Considere em ajudar a traduzir o HTML Tidy. \n"
        "Para mais detalhes, por favor veja: \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },
    { ADDED_MISSING_CHARSET,                         0, "Adicionado o <meta charset=...> apropriado em falta ao %s"                                       },
    { ANCHOR_NOT_UNIQUE,                             0, "??ncora de %s \"%s\" j?? est?? definido"                                                            },
    { APOS_UNDEFINED,                                0, "a entidade declarada &apos; s?? definida em XML/XHTML"                                            },
    { ATTR_VALUE_NOT_LCASE,                          0, "valor do atributo de %s \"%s\" deve ser min??sculo para XHTML"                                    },
    { ATTRIBUTE_IS_NOT_ALLOWED,                      0, "atributo de %s \"is\" n??o permitido para tags personalizadas aut??nomas."                         },
    { ATTRIBUTE_VALUE_REPLACED,                      0, "atributo %s \"%s\", valor incorreto \"%s\" substitu??do"                                          },
    { BACKSLASH_IN_URI,                              0, "refer??ncia da URI %s cont??m barra invertida. Erro de escrita?"                                   },
    { BAD_ATTRIBUTE_VALUE_REPLACED,                  0, "atributo %s \"%s\" tinha valor inv??lido \"%s\" e foi substitu??do"                                },
    { BAD_ATTRIBUTE_VALUE,                           0, "atributo %s \"%s\" possui valor inv??lido \"%s\""                                                 },
    { BAD_CDATA_CONTENT,                             0, "'<' + '/' + letra n??o permitido aqui"                                                            },
    { BAD_SUMMARY_HTML5,                             0, "O atributo de resumo no elemento %s ?? obsoleto no HTML5"                                         },
    { BAD_SURROGATE_LEAD,                            0,        
        "Par substituto ao final (baixo) U+%04X, com nenhuma entidade precedente "
        "(Alta), substitu??do por U+FFFD."
    },
    { BAD_SURROGATE_PAIR,                            0,        
        "Possui par substituto U+%04X:U+%04X fora do intervalo, substitu??do pelo "
        "valor U+FFFD."
    },
    { BAD_SURROGATE_TAIL,                            0,        
        "Par substituto precedente (alto) U+%04X, com nenhuma entidade ao final "
        "(Baixo), substitu??do por U+FFFD."
    },
    { CANT_BE_NESTED,                                0, "%s n??o pode ser aninhado"                                                                        },
    { COERCE_TO_ENDTAG,                              0, "<%s> provavelmente deveria ser </%s>"                                                            },
    { CONTENT_AFTER_BODY,                            0, "o conte??do ocorre ap??s o fim do corpo"                                                           },
    { CUSTOM_TAG_DETECTED,                           0, "tag personalizada aut??noma %s detectada; ser?? tratada como %s"                                   },
    { DISCARDING_UNEXPECTED,                         0, "descartando %s inesperado"                                                                       },
    { DOCTYPE_AFTER_TAGS,                            0, "<!DOCTYPE> n??o ?? permitido ap??s elementos"                                                       },
    { DUPLICATE_FRAMESET,                            0, "elemento FRAMESET repetido"                                                                      },
    { ELEMENT_NOT_EMPTY,                             0, "%s elemento n??o vazio ou n??o fechado"                                                            },
    { ELEMENT_VERS_MISMATCH_ERROR,                   0, "%s elemento n??o dispon??vel na %s"                                                                },
    { ELEMENT_VERS_MISMATCH_WARN,                    0, "%s elemento n??o dispon??vel na %s"                                                                },
    { ENCODING_MISMATCH,                             0,        
        "a codifica????o de entrada especificada (%s) n??o corresponde ?? codifica????o de "
        "entrada atual (%s)"
    },
    { ESCAPED_ILLEGAL_URI,                           0, "%s escapando refer??ncia de URI malformada"                                                       },
    { FILE_CANT_OPEN,                                0, "N??o foi poss??vel abrir \"%s\"\n"                                                                 },
    { FILE_CANT_OPEN_CFG,                            0, "N??o foi poss??vel abrir o arquivo de configura????o \"%s\"\n"                                       },
    { FILE_NOT_FILE,                                 0, "\"%s\" n??o ?? um arquivo!\n"                                                                      },
    { FIXED_BACKSLASH,                               0, "%s convertendo barra invertida em URI para barra"                                                },
    { FOUND_STYLE_IN_BODY,                           0, "encontrada tag <style> em <body>! fix-style-tags: yes para mover."                               },
    { ID_NAME_MISMATCH,                              0, "%s valores dos atributos id e name incompat??veis"                                                },
    { ILLEGAL_NESTING,                               0, "%s n??o devem ser aninhados"                                                                      },
    { ILLEGAL_URI_CODEPOINT,                         0, "%s caracteres ilegais localizados na URI"                                                        },
    { ILLEGAL_URI_REFERENCE,                         0, "refer??ncia de URI %s inadequadamente escapada"                                                   },
    { INSERTING_AUTO_ATTRIBUTE,                      0, "%s inserindo atributo \"%s\" usando valor \"%s\""                                                },
    { INSERTING_TAG,                                 0, "inserindo <%s> impl??cita"                                                                        },
    { INVALID_ATTRIBUTE,                             0, "nome do atributo de %s \"%s\" (valor=\"%s\") ?? inv??lido"                                         },
    { INVALID_NCR,                                   0, "%s refer??ncia de caractere num??rico %s"                                                          },
    { INVALID_SGML_CHARS,                            0, "%s c??digo de caracteres inv??lido %s"                                                             },
    { INVALID_UTF8,                                  0, "%s bytes de UTF-8 inv??lido (c??digo de caracteres %s)"                                            },
    { INVALID_UTF16,                                 0, "%s par de substituto de UTF-16 inv??lido (c??digo de caracteres %s)"                               },
    { INVALID_XML_ID,                                0, "%s n??o p??de copiar atributo de nome para id"                                                     },
    { JOINING_ATTRIBUTE,                             0, "%s juntando valores de atributo repetido \"%s\""                                                 },
    { MALFORMED_COMMENT,                             0, "h??fenes adjacentes dentro de coment??rio"                                                         },
    { MALFORMED_DOCTYPE,                             0, "descartando <!DOCTYPE> malformado"                                                               },
    { MISMATCHED_ATTRIBUTE_ERROR,                    0, "atributo de %s \"%s\" n??o permitido para %s"                                                     },
    { MISMATCHED_ATTRIBUTE_WARN,                     0, "atributo de %s \"%s\" n??o permitido para %s"                                                     },
    { MISSING_ATTR_VALUE,                            0, "atributo de %s \"%s\" carece de valor"                                                           },
    { MISSING_ATTRIBUTE,                             0, "%s carece de atributo \"%s\""                                                                    },
    { MISSING_DOCTYPE,                               0, "faltando declara????o <!DOCTYPE>"                                                                  },
    { MISSING_ENDTAG_BEFORE,                         0, "faltando </%s> antes de %s"                                                                      },
    { MISSING_ENDTAG_FOR,                            0, "faltando </%s>"                                                                                  },
    { MISSING_IMAGEMAP,                              0, "%s deve usar mapa de imagem no lado de cliente"                                                  },
    { MISSING_QUOTEMARK,                             0, "atributo de %s faltando aspas ao final"                                                          },
    { MISSING_SEMICOLON_NCR,                         0, "refer??ncia de caractere num??rico \"%s\" n??o termina em ';'"                                      },
    { MISSING_SEMICOLON,                             0, "entidade \"%s\" n??o termina em ';'"                                                              },
    { MISSING_STARTTAG,                              0, "faltando <%s>"                                                                                   },
    { MISSING_TITLE_ELEMENT,                         0, "inserindo elemento faltante 'title'"                                                             },
    { MOVED_STYLE_TO_HEAD,                           0, "tag <style> movida para <head>! fix-style-tags: no para evitar."                                 },
    { NESTED_EMPHASIS,                               0, "??nfase aninhada %s"                                                                              },
    { NESTED_QUOTATION,                              0, "elementos q aninhados, poss??vel erro de escrita."                                                },
    { NEWLINE_IN_URI,                                0, "%s descartando nova linha na refer??ncia de URI"                                                  },
    { NOFRAMES_CONTENT,                              0, "%s n??o dentre de elemento 'noframes'"                                                            },
    { NON_MATCHING_ENDTAG,                           0, "substituindo %s inesperada por </%s>"                                                            },
    { OBSOLETE_ELEMENT,                              0, "substituindo elemento obsoleto %s por %s"                                                        },
    { PREVIOUS_LOCATION,                             0, "<%s> anteriormente mencionada"                                                                   },
    { PROPRIETARY_ATTR_VALUE,                        0, "atributo propriet??rio %s com valor \"%s\""                                                       },
    { PROPRIETARY_ATTRIBUTE,                         0, "atributo propriet??rio %s \"%s\""                                                                 },
    { PROPRIETARY_ELEMENT,                           0, "%s n??o ?? aprovado pela W3C"                                                                      },
    { REMOVED_HTML5,                                 0, "elemento %s removido do HTML5"                                                                   },
    { REPEATED_ATTRIBUTE,                            0, "%s descartando valor \"%s\" para atributo repetido \"%s\""                                       },
    { REPLACING_ELEMENT,                             0, "substituindo %s por %s"                                                                          },
    { REPLACING_UNEX_ELEMENT,                        0, "substituindo %s inesperada por %s"                                                               },
    { SPACE_PRECEDING_XMLDECL,                       0, "removendo espa??o em branco precedendo a declara????o XML"                                          },
    { STRING_MISSING_MALFORMED,                      0, "argumento faltando ou malformado para op????o: %s"                                                 },
    { STRING_UNKNOWN_OPTION,                         0, "op????o desconhecida: %s"                                                                          },
    { SUSPECTED_MISSING_QUOTE,                       0, "faltando aspas para o valor de atributo"                                                         },
    { TAG_NOT_ALLOWED_IN,                            0, "%s n??o ?? permitido em elementos <%s>"                                                            },
    { TOO_MANY_ELEMENTS_IN,                          0, "n??mero excessivo de elementos %s em <%s>"                                                        },
    { TOO_MANY_ELEMENTS,                             0, "n??mero excessivo de elementos %s"                                                                },
    { TRIM_EMPTY_ELEMENT,                            0, "aparando %s vazio"                                                                               },
    { UNESCAPED_AMPERSAND,                           0, "& n??o escapado que deve ser escrito como &amp;"                                                  },
    { UNEXPECTED_END_OF_FILE_ATTR,                   0, "%s fim de arquivo enquanto analisava atributos"                                                  },
    { UNEXPECTED_END_OF_FILE,                        0, "fim do arquivo %s inesperado"                                                                    },
    { UNEXPECTED_ENDTAG_ERR,                         0, "</%s> inesperada"                                                                                },
    { UNEXPECTED_ENDTAG_IN,                          0, "</%s> inesperada em <%s>"                                                                        },
    { UNEXPECTED_ENDTAG,                             0, "</%s> inesperada"                                                                                },
    { UNEXPECTED_EQUALSIGN,                          0, "%s inesperado '=', esperava nome de atributo"                                                    },
    { UNEXPECTED_GT,                                 0, "%s carece de '>' para o fim da tag"                                                              },
    { UNEXPECTED_QUOTEMARK,                          0, "%s aspas inesperadas ou duplicadas"                                                              },
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM,                  0, "%s n??o ?? reconhecido! Voc?? queria habilitar a op????o custom-tags?"                                },
    { UNKNOWN_ELEMENT,                               0, "%s n??o ?? reconhecido!"                                                                           },
    { UNKNOWN_ENTITY,                                0, "& n??o escapado ou entidade desconhecida \"%s\""                                                  },
    { USING_BR_INPLACE_OF,                           0, "usando <br> no lugar de %s"                                                                      },
    { VENDOR_SPECIFIC_CHARS,                         0, "%s c??digo de caractere inv??lido %s"                                                              },
    { WHITE_IN_URI,                                  0, "%s descartando espa??o em branco na refer??ncia de URI"                                            },
    { XML_DECLARATION_DETECTED,                      0, "Uma declara????o XML foi detectada. Voc?? queria usar input-xml?"                                   },
    { XML_ID_SYNTAX,                                 0, "%s ID \"%s\" usa sintaxe de ID de XML"                                                           },
    { IMG_MISSING_ALT,                               0, "[1.1.1.1]: <img> carece de texto 'alt'."                                                         },
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0, "[1.1.1.2]: texto 'alt' suspeito (nome de arquivo)."                                              },
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0, "[1.1.1.3]: texto 'alt' suspeito (tamanho de arquivo)."                                           },
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0, "[1.1.1.4]: texto 'alt' suspeito (espa??o reservado)."                                             },
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0, "[1.1.1.10]: texto 'alt' suspeito (longo demais)."                                                },
    { IMG_MISSING_LONGDESC_DLINK,                    0, "[1.1.2.1]: <img> carece de 'longdesc' e d-link."                                                 },
    { IMG_MISSING_DLINK,                             0, "[1.1.2.2]: <img> carece de d-link."                                                              },
    { IMG_MISSING_LONGDESC,                          0, "[1.1.2.3]: <img> carece de 'longdesc'."                                                          },
    { IMG_BUTTON_MISSING_ALT,                        0, "[1.1.3.1]: <img> (bot??o) carece de texto 'alt'."                                                 },
    { APPLET_MISSING_ALT,                            0, "[1.1.4.1]: <applet> carece de conte??do alternativo."                                             },
    { OBJECT_MISSING_ALT,                            0, "[1.1.5.1]: <object> carece de conte??do alternativo."                                             },
    { AUDIO_MISSING_TEXT_WAV,                        0, "[1.1.6.1]: ??udio carece de transcri????o de texto (wav)."                                          },
    { AUDIO_MISSING_TEXT_AU,                         0, "[1.1.6.2]: ??udio carece de transcri????o de texto (au)."                                           },
    { AUDIO_MISSING_TEXT_AIFF,                       0, "[1.1.6.3]: ??udio carece de transcri????o de texto (aiff)."                                         },
    { AUDIO_MISSING_TEXT_SND,                        0, "[1.1.6.4]: ??udio carece de transcri????o de texto (snd)."                                          },
    { AUDIO_MISSING_TEXT_RA,                         0, "[1.1.6.5]: ??udio carece de transcri????o de texto (ra)."                                           },
    { AUDIO_MISSING_TEXT_RM,                         0, "[1.1.6.6]: ??udio carece de transcri????o de texto (rm)."                                           },
    { FRAME_MISSING_LONGDESC,                        0, "[1.1.8.1]: <frame> pode exigir 'longdesc'."                                                      },
    { AREA_MISSING_ALT,                              0, "[1.1.9.1]: <area> carece de texto 'alt'."                                                        },
    { SCRIPT_MISSING_NOSCRIPT,                       0, "[1.1.10.1]: <script> carece de se????o <noscript>."                                                },
    { ASCII_REQUIRES_DESCRIPTION,                    0, "[1.1.12.1]: arte em ascii exige descri????o."                                                      },
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0, "[1.2.1.1]: mapa de imagem (lado do servidor) exige links de texto."                              },
    { MULTIMEDIA_REQUIRES_TEXT,                      0, "[1.4.1.1]: multim??dia exibe equivalentes de texto sincronizado."                                 },
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0, "[1.5.1.1]: mapa da imagem (lado do cliente) carece de links de texto."                           },
    { INFORMATION_NOT_CONVEYED_IMAGE,                0, "[2.1.1.1]: certificar de que as informa????es n??o sejam transmitidas apenas por cores (imagem)."   },
    { INFORMATION_NOT_CONVEYED_APPLET,               0, "[2.1.1.2]: certificar de que as informa????es n??o sejam transmitidas apenas por cores (applet)."   },
    { INFORMATION_NOT_CONVEYED_OBJECT,               0, "[2.1.1.3]: certificar de que as informa????es n??o sejam transmitidas apenas por cores (objeto)."   },
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0, "[2.1.1.4]: certificar de que as informa????es n??o sejam transmitidas apenas por cores (script)."   },
    { INFORMATION_NOT_CONVEYED_INPUT,                0,        
        "[2.1.1.5]: certificar de que as informa????es n??o sejam transmitidas apenas por cores "
        "(entrada)."
    },
    { COLOR_CONTRAST_TEXT,                           0, "[2.2.1.1]: contraste de cores ruim (texto)."                                                     },
    { COLOR_CONTRAST_LINK,                           0, "[2.2.1.2]: contraste de cores ruim (link)."                                                      },
    { COLOR_CONTRAST_ACTIVE_LINK,                    0, "[2.2.1.3]: contraste de cores ruim (link ativo)."                                                },
    { COLOR_CONTRAST_VISITED_LINK,                   0, "[2.2.1.4]: contraste de cores ruim (link visitado)."                                             },
    { DOCTYPE_MISSING,                               0, "[3.2.1.1]: faltando <doctype>."                                                                  },
    { STYLE_SHEET_CONTROL_PRESENTATION,              0, "[3.3.1.1]: use folhas de estilo para controlar apresenta????o."                                    },
    { HEADERS_IMPROPERLY_NESTED,                     0, "[3.5.1.1]: cabe??alhos aninhados incorretamente."                                                 },
    { POTENTIAL_HEADER_BOLD,                         0, "[3.5.2.1]: cabe??alho potencial (negrito)."                                                       },
    { POTENTIAL_HEADER_ITALICS,                      0, "[3.5.2.2]: cabe??alho potencial (it??lico)."                                                       },
    { POTENTIAL_HEADER_UNDERLINE,                    0, "[3.5.2.3]: cabe??alho potencial (sublinhado)."                                                    },
    { HEADER_USED_FORMAT_TEXT,                       0, "[3.5.3.1]: cabe??alho usado para formatar o texto."                                               },
    { LIST_USAGE_INVALID_UL,                         0, "[3.6.1.1]: uso de lista inv??lido <ul>."                                                          },
    { LIST_USAGE_INVALID_OL,                         0, "[3.6.1.2]: uso de lista inv??lido <ol>."                                                          },
    { LIST_USAGE_INVALID_LI,                         0, "[3.6.1.4]: uso de lista inv??lido <li>."                                                          },
    { LANGUAGE_NOT_IDENTIFIED,                       0, "[4.3.1.1]: idioma n??o identificado."                                                             },
    { LANGUAGE_INVALID,                              0, "[4.3.1.2]: atributo de idioma inv??lido."                                                         },
    { DATA_TABLE_MISSING_HEADERS,                    0, "[5.1.2.1]: <table> de dados carece de cabe??alhos de linha/coluna (todos)."                       },
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0, "[5.1.2.2]: <table> de dados carece de cabe??alhos de linha/coluna (1 col)."                       },
    { DATA_TABLE_MISSING_HEADERS_ROW,                0, "[5.1.2.3]: <table> de dados carece de cabe??alhos de linha/coluna (1 lin)."                       },
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0, "[5.2.1.1]: <table> pode exigir marca????o (cabe??alhos de coluna)."                                 },
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0, "[5.2.1.2]: <table> pode exigir marca????o (cabe??alhos de linha)."                                  },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0, "[5.3.1.1]: verifique se tabelas de layout linearizaram corretamente."                            },
    { LAYOUT_TABLE_INVALID_MARKUP,                   0, "[5.4.1.1]: marca????o inv??lida usada em <table> de layout."                                        },
    { TABLE_MISSING_SUMMARY,                         0, "[5.5.1.1]: <table> carece de sum??rio."                                                           },
    { TABLE_SUMMARY_INVALID_NULL,                    0, "[5.5.1.2]: resumo da <table> inv??lido (nulo)."                                                   },
    { TABLE_SUMMARY_INVALID_SPACES,                  0, "[5.5.1.3]: resumo da <table> inv??lido (espa??os)."                                                },
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0, "[5.5.1.6]: resumo da <table> inv??lido (texto de espa??o reservado)."                              },
    { TABLE_MISSING_CAPTION,                         0, "[5.5.2.1]: <table> carece de <caption>."                                                         },
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0, "[5.6.1.1]: <table> pode exigir abrevia????es de cabe??alho."                                        },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0, "[5.6.1.2]: abrevia????es de cabe??alho de <table> inv??lidas (nula)."                                },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0, "[5.6.1.3]: abrevia????es de cabe??alho de <table> inv??lidas (espa??os)."                             },
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0, "[6.1.1.1]: folhas de estilo exigem teste (link)."                                                },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0, "[6.1.1.2]: folhas de estilo exigem teste (elemento de estilo)."                                  },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0, "[6.1.1.3]: folhas de estilo exigem teste (atributo de estilo)."                                  },
    { FRAME_SRC_INVALID,                             0, "[6.2.1.1]: fonte de <frame> inv??lida."                                                           },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0, "[6.2.2.1]: equivalentes de texto exigem atualiza????o (applet)."                                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0, "[6.2.2.2]: equivalentes de texto exigem atualiza????o (script)."                                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0, "[6.2.2.3]: equivalentes de texto exigem atualiza????o (object)."                                   },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0, "[6.3.1.1]: objetos program??ticos exigem teste (script)."                                         },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0, "[6.3.1.2]: objetos program??ticos exigem teste (object)."                                         },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0, "[6.3.1.3]: objetos program??ticos exigem teste (embed)."                                          },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0, "[6.3.1.4]: objetos program??ticos exigem teste (applet)."                                         },
    { FRAME_MISSING_NOFRAMES,                        0, "[6.5.1.1]: <frameset> carece de se????o <noframes>."                                               },
    { NOFRAMES_INVALID_NO_VALUE,                     0, "[6.5.1.2]: se????o <noframes> inv??lida (sem valor)."                                               },
    { NOFRAMES_INVALID_CONTENT,                      0, "[6.5.1.3]: se????o <noframes> inv??lida (conte??do)."                                                },
    { NOFRAMES_INVALID_LINK,                         0, "[6.5.1.4]: se????o <noframes> inv??lida (link)."                                                    },
    { REMOVE_FLICKER_SCRIPT,                         0, "[7.1.1.1]: remo????o de cintila????o (script)."                                                      },
    { REMOVE_FLICKER_OBJECT,                         0, "[7.1.1.2]: remo????o de cintila????o (object)."                                                      },
    { REMOVE_FLICKER_EMBED,                          0, "[7.1.1.3]: remo????o de cintila????o (embed)."                                                       },
    { REMOVE_FLICKER_APPLET,                         0, "[7.1.1.4]: remo????o de cintila????o (applet)."                                                      },
    { REMOVE_FLICKER_ANIMATED_GIF,                   0, "[7.1.1.5]: remo????o de cintila????o (gif animado)."                                                 },
    { REMOVE_BLINK_MARQUEE,                          0, "[7.2.1.1]: remo????o de blink/marquee."                                                            },
    { REMOVE_AUTO_REFRESH,                           0, "[7.4.1.1]: remo????o de autorrenova????o."                                                           },
    { REMOVE_AUTO_REDIRECT,                          0, "[7.5.1.1]: remo????o de autorredirecionamento."                                                    },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0, "[8.1.1.1]: certifique-se que objetos program??ticos sejam acess??veis (script)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0, "[8.1.1.2]: certifique-se que objetos program??ticos sejam acess??veis (object)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0, "[8.1.1.3]: certifique-se que objetos program??ticos sejam acess??veis (applet)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0, "[8.1.1.43]: certifique-se que objetos program??ticos sejam acess??veis (embed)."                   },
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0, "[9.1.1.1]: mapa de imagem (lado do servidor) exige convers??o."                                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0, "[9.3.1.1]: <script> n??o ?? acess??vel por teclado (onMouseDown)."                                  },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0, "[9.3.1.2]: <script> n??o ?? acess??vel por teclado (onMouseUp)."                                    },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0, "[9.3.1.3]: <script> n??o ?? acess??vel por teclado (onClick)."                                      },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0, "[9.3.1.4]: <script> n??o ?? acess??vel por teclado (onMouseOver)."                                  },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0, "[9.3.1.5]: <script> n??o ?? acess??vel por teclado (onMouseOut)."                                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0, "[9.3.1.6]: <script> n??o ?? acess??vel por teclado (onMouseMove)."                                  },
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0, "[10.1.1.1]: novas janelas exigem aviso (_new)."                                                  },
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0, "[10.1.1.2]: novas janelas exigem aviso (_blank)."                                                },
    { REPLACE_DEPRECATED_HTML_APPLET,                0, "[11.2.1.1]: substituir o elemento html obsoleto <applet>."                                       },
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0, "[11.2.1.2]: substituir o elemento html obsoleto <basefont>."                                     },
    { REPLACE_DEPRECATED_HTML_CENTER,                0, "[11.2.1.3]: substituir o elemento html obsoleto <center>."                                       },
    { REPLACE_DEPRECATED_HTML_DIR,                   0, "[11.2.1.4]: substituir o elemento html obsoleto <dir>."                                          },
    { REPLACE_DEPRECATED_HTML_FONT,                  0, "[11.2.1.5]: substituir o elemento html obsoleto <font>."                                         },
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0, "[11.2.1.6]: substituir o elemento html obsoleto <isindex>."                                      },
    { REPLACE_DEPRECATED_HTML_MENU,                  0, "[11.2.1.7]: substituir o elemento html obsoleto <menu>."                                         },
    { REPLACE_DEPRECATED_HTML_S,                     0, "[11.2.1.8]: substituir o elemento html obsoleto <s>."                                            },
    { REPLACE_DEPRECATED_HTML_STRIKE,                0, "[11.2.1.9]: substituir o elemento html obsoleto <strike>."                                       },
    { REPLACE_DEPRECATED_HTML_U,                     0, "[11.2.1.10]: substituir o elemento html obsoleto <u>."                                           },
    { FRAME_MISSING_TITLE,                           0, "[12.1.1.1]: <frame> carece de t??tulo."                                                           },
    { FRAME_TITLE_INVALID_NULL,                      0, "[12.1.1.2]: t??tulo de <frame> inv??lido (nulo)."                                                  },
    { FRAME_TITLE_INVALID_SPACES,                    0, "[12.1.1.3]: t??tulo de <frame> inv??lido (espa??os)."                                               },
    { ASSOCIATE_LABELS_EXPLICITLY,                   0, "[12.4.1.1]: associar r??tulos explicitamente com controles de formul??rio."                        },
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0,        
        "[12.4.1.2]: associar r??tulos explicitamente com controles de formul??rio "
        "(for)."
    },
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0, "[12.4.1.3]: associar r??tulos explicitamente com controles de formul??rio (id)."                   },
    { LINK_TEXT_NOT_MEANINGFUL,                      0, "[13.1.1.1]: texto de link n??o significativo."                                                    },
    { LINK_TEXT_MISSING,                             0, "[13.1.1.2]: faltando texto de link."                                                             },
    { LINK_TEXT_TOO_LONG,                            0, "[13.1.1.3]: texto de link longo demais."                                                         },
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0, "[13.1.1.4]: texto de link n??o significativo (clique aqui)."                                      },
    { METADATA_MISSING,                              0, "[13.2.1.1]: faltando metadados."                                                                 },
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0, "[13.2.1.3]: faltando metadados (redirecionamento/autorrenova????o)."                               },
    { SKIPOVER_ASCII_ART,                            0, "[13.10.1.1]: pular arte em ascii."                                                               },

#if SUPPORT_CONSOLE_APP
    { TC_LABEL_COL,                                  0, "coluna"                                                                                          },
    { TC_LABEL_FILE,                                 0, "arquivo"                                                                                         },
    { TC_LABEL_LANG,                                 0, "idioma"                                                                                          },
    { TC_LABEL_LEVL,                                 0, "n??vel"                                                                                           },
    { TC_LABEL_OPT,                                  0, "op????o"                                                                                           },
    { TC_MAIN_ERROR_LOAD_CONFIG,                     0, "Falha ao carregar o arquivo de config \"%s\", err = %d"                                          },
    { TC_OPT_ACCESS,                                 0,        
        " faz verifica????es adicionais de acessibilidade (<n??vel> = 0, 1, 2, 3). 0 ?? "
        "presumido se <n??vel> estiver faltando."
    },
    { TC_OPT_ASCII,                                  0, "usa ISO-8859-1 para entrada, US-ASCII para sa??da"                                                },
    { TC_OPT_ASHTML,                                 0, "for??a XHTML para HTML bem formatado"                                                             },
    { TC_OPT_ASXML,                                  0, "converte HTML para XHTML bem formatado"                                                          },
    { TC_OPT_BARE,                                   0, "retira aspas inteligentes, travess??es etc."                                                      },
    { TC_OPT_BIG5,                                   0, "usa Big5 para tanto entrada quanto sa??da"                                                        },
    { TC_OPT_CLEAN,                                  0, "substitui tags FONT, NOBR e CENTER com CSS"                                                      },
    { TC_OPT_CONFIG,                                 0, "define op????es de configura????o a partir do <arquivo> especificado"                                },
    { TC_OPT_ERRORS,                                 0, "mostra apenas erros e avisos"                                                                    },
    { TC_OPT_FILE,                                   0, "escreve erros e avisos para o <arquivo> especificado"                                            },
    { TC_OPT_GDOC,                                   0, "produz vers??o limpa do html exportado pelo Google Docs"                                          },
    { TC_OPT_HELP,                                   0, "lista as op????es de linha de comando"                                                             },
    { TC_OPT_HELPCFG,                                0, "lista todas as op????es de configura????o"                                                           },
    { TC_OPT_HELPOPT,                                0, "  mostra uma descri????o da <op????o>"                                                               },
    { TC_OPT_IBM858,                                 0, "usa IBM-858 (CP850+Euro) para entrada, US-ASCII para sa??da"                                      },
    { TC_OPT_INDENT,                                 0, "recua o conte??do do elemento"                                                                    },
    { TC_OPT_ISO2022,                                0, "usa ISO-2022 para tanto entrada quanto sa??da"                                                    },
    { TC_OPT_LANGUAGE,                               0,        
        "define o idioma de sa??da do Tidy para <idioma>. Especifique '-language help' "
        "para mais ajuda. Use antes de argumentos que gerem sa??da para garantir que o "
        "idioma surta efeitos, p.ex.:\n"
        "`tidy -lang es -lang help`."
    },
    { TC_OPT_LATIN0,                                 0, "usa ISO-8859-15 para entrada, US-ASCII para sa??da"                                               },
    { TC_OPT_LATIN1,                                 0, "usa ISO-8859-1 para tanto entrada quanto sa??da"                                                  },
    { TC_OPT_MAC,                                    0, "usa MacRoman para entrada, US-ASCII para sa??da"                                                  },
    { TC_OPT_MODIFY,                                 0, "modifica os arquivos de entrada originais"                                                       },
    { TC_OPT_NUMERIC,                                0, "emite entidades num??ricas em vez de nomeadas"                                                    },
    { TC_OPT_OMIT,                                   0, "omite tags opcionais de in??cio e de fim"                                                         },
    { TC_OPT_OUTPUT,                                 0, "escreve a sa??da para o <arquivo> especificado"                                                   },
    { TC_OPT_QUIET,                                  0, "suprime sa??da n??o essencial"                                                                     },
    { TC_OPT_RAW,                                    0, "emite valores acima de 127 sem convers??o para entidades"                                         },
    { TC_OPT_SHIFTJIS,                               0, "usa Shift_JIS para tanto entrada quanto sa??da"                                                   },
    { TC_OPT_SHOWCFG,                                0, "lista as defini????es da configura????o atual"                                                       },
    { TC_OPT_UPPER,                                  0, "for??a tags para mai??sculo"                                                                       },
    { TC_OPT_UTF16,                                  0, "usa UTF-16 para tanto entrada quanto sa??da"                                                      },
    { TC_OPT_UTF16BE,                                0, "usa UTF-16BE para tanto entrada quanto sa??da"                                                    },
    { TC_OPT_UTF16LE,                                0, "usa UTF-16LE para tanto entrada quanto sa??da"                                                    },
    { TC_OPT_UTF8,                                   0, "usa UTF-8 para tanto entrada quanto sa??da"                                                       },
    { TC_OPT_VERSION,                                0, "mostra a vers??o do Tidy"                                                                         },
    { TC_OPT_WIN1252,                                0, "usa Windows--1252 para entrada, US-ASCII para sa??da"                                             },
    { TC_OPT_WRAP,                                   0,        
        "efetua quebra de texto na <coluna> especificada, 0 ?? presumido se <coluna> "
        "estiver faltando. Quando esta op????o ?? omitida, o padr??o da op????o da "
        "configura????o 'wrap' ?? aplicado."
    },
    { TC_OPT_XML,                                    0, "especifica a entrada ?? XML bem formatado"                                                        },
    { TC_OPT_XMLCFG,                                 0, "lista todas as op????es de configura????o no formato XML"                                            },
    { TC_OPT_XMLHELP,                                0, "lista as op????es de linha de comando no formato XML"                                              },
    { TC_OPT_XMLSTRG,                                0, "emite todas as strings do Tidy no formato XML"                                                   },
    { TC_OPT_XMLERRS,                                0, "emite constantes de erro e strings no formato XML"                                               },
    { TC_OPT_XMLOPTS,                                0, "emite descri????es de op????o no formato XML"                                                        },
    { TC_STRING_CONF_HEADER,                         0, "Defini????es do arquivo de configura????o:"                                                          },
    { TC_STRING_CONF_NAME,                           0, "Nome"                                                                                            },
    { TC_STRING_CONF_TYPE,                           0, "Tipo"                                                                                            },
    { TC_STRING_CONF_VALUE,                          0, "Valor atual"                                                                                     },
    { TC_STRING_OPT_NOT_DOCUMENTED,                  0, "Aviso: a op????o '%s' n??o est?? documentada."                                                       },
    { TC_STRING_OUT_OF_MEMORY,                       0, "Mem??ria insuficiente. Saindo."                                                                   },
    { TC_STRING_FATAL_ERROR,                         0, "Erro fatal: valor imposs??vel para id='%d'."                                                      },
    { TC_STRING_FILE_MANIP,                          0, "Manipula????o de arquivo"                                                                          },
    { TC_STRING_PROCESS_DIRECTIVES,                  0, "Diretivas de processamento"                                                                      },
    { TC_STRING_CHAR_ENCODING,                       0, "Codifica????es de caracteres"                                                                      },
    { TC_STRING_LANG_MUST_SPECIFY,                   0, "Uma localidade POSIX ou Windows deve ser especificada."                                          },
    { TC_STRING_LANG_NOT_FOUND,                      0, "Tidy n??o possui o idioma '%s'; em vez desta, usar?? '%s'."                                        },
    { TC_STRING_MISC,                                0, "Diversos"                                                                                        },
    { TC_STRING_XML,                                 0, "XML"                                                                                             },
    { TC_STRING_MUST_SPECIFY,                        0, "Um nome de op????o Tidy deve ser especificado."                                                    },
    { TC_STRING_UNKNOWN_OPTION,                      0, "HTML Tidy: op????o desconhecida: %c"                                                               },
    { TC_STRING_UNKNOWN_OPTION_B,                    0, "HTML Tidy: op????o desconhecida."                                                                  },
    { TC_STRING_VERS_A,                              0, "HTML Tidy para %s vers??o %s"                                                                     },
    { TC_STRING_VERS_B,                              0, "HTML Tidy vers??o %s"                                                                             },
    { TC_TXT_HELP_1,                                 0,        
        "\n"
        "%s [op????es...] [arquivo...] [op????es...] [arquivo...]\n"
        "Utilit??rio para limpar e melhor imprimir HTML/XHTML/XML.\n"
        "\n"
        "Essa ?? o HTML Tidy moderno vers??o %s.\n"
        "\n"
    },
    { TC_TXT_HELP_2A,                                0, "Os argumentos de linha de comando para HTML Tidy para %s:"                                       },
    { TC_TXT_HELP_2B,                                0, "Os argumentos de linha de comando para HTML Tidy:"                                               },
    { TC_TXT_HELP_3,                                 0,        
        "\n"
        "Op????es de configura????o do Tidy\n"
        "==========================\n"
        "Use as op????es de configura????o do Tidy como argumentos de linha de comando\n"
        "no forma de \"--alguma-opcao <valor>\", por exemplo \"--indent-with-tabs "
        "yes\".\n"
        "\n"
        "Para uma lista de todas as op????es de configura????o, use \"-help-config\" ou\n"
        "veja a p??gina man (se seu SO tiver uma).\n"
        "\n"
        "Se seu ambiente tem uma vari??vel $HTML_TIDY definida, aponte para um "
        "arquivo\n"
        "de configura????o Tidy e, ent??o, Tidy vai tentar us??-la.\n"
        "\n"
        "Em algumas plataformas, Tidy tamb??m vai tentar usar uma configura????o\n"
        "especificada no /etc/tidy.conf ou ~/.tidy.conf.\n"
        "\n"
        "Outro\n"
        "=====\n"
        "Entrada/Sa??da usa, por padr??o, stdin/stdout respectivamente.\n"
        "\n"
        "Op????es de uma s?? letra, com exce????o de -f, podem ser combinadas\n"
        "como em: tidy -f errs.txt -imu foo.html\n"
        "\n"
        "Informa????o\n"
        "===========\n"
        "Para mais informa????es sobre HTML Tidy, veja\n"
        "  http://www.html-tidy.org/\n"
        "\n"
        "Para mais informa????es sobre HTML, veja o seguinte:\n"
        "\n"
        "  HTML: Edition for Web Authors (the latest HTML specification)\n"
        "  http://dev.w3.org/html5/spec-author-view\n"
        "\n"
        "  HTML: The Markup Language (an HTML language reference)\n"
        "  http://dev.w3.org/html5/markup/\n"
        "\n"
        "Preencha relat??rios de erros em https://github.com/htacg/tidy-html5/issues/\n"
        "ou envie perguntas e coment??rios para public-htacg@w3.org.\n"
        "\n"
        "Valide seus documentos HTML usando Nu, o validador de marca????o da W3C:\n"
        "  http://validator.w3.org/nu/\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG,                            0,        
        "\n"
        "Defini????es de configura????o do HTML Tidy\n"
        "\n"
        "Dentro de um arquivo, use a forma:\n"
        "\n"
        "wrap: 72\n"
        "indent: no\n"
        "\n"
        "Quando especificado na linha de comando, use a forma:\n"
        "\n"
        "--wrap 72 --indent no\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,                       0, "Nome"                                                                                            },
    { TC_TXT_HELP_CONFIG_TYPE,                       0, "Tipo"                                                                                            },
    { TC_TXT_HELP_CONFIG_ALLW,                       0, "Valores permitidos"                                                                              },
    { TC_TXT_HELP_LANG_1,                            0,        
        "\n"
        "A op????o -language (ou -lang) indica qual idioma o Tidy deve usar\n"
        "para comunicar sua sa??da. Por favor, note que este n??o ?? um servi??o\n"
        "de tradu????o de documentos e afeta apenas as mensagens com as quais\n"
        "o Tidy se comunica com voc??.\n"
        "\n"
        "Quando usado a partir da linha de comando, o argumento -language\n"
        "deve ser usado antes de qualquer argumento que resulte em sa??da; do\n"
        "contr??rio, o Tidy produzir?? sa??da antes de saber qual idioma usar.\n"
        "\n"
        "Al??m dos c??digos de idioma POSIX padr??o, o Tidy ?? capaz de entender\n"
        "os c??digos legados de idioma do Windows. Por favor, note que esta\n"
        "lista indica c??digos Tidy entende e n??o indica que o idioma esteja\n"
        "instalado no momento.\n"
        "\n"
        "A coluna mais ?? direita indica como o Tidy vai entender o nome do\n"
        "Windows legado.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,                            0,        
        "\n"
        "Os seguintes idiomas est??o atualmente instalados em Tidy. Por favor, \n"
        "note que n??o h?? garantia de que eles estejam completos; apenas que \n"
        "esse desenvolvedor ou outro come??ou a adicionar o idioma indicado. \n"
        "\n"
        "As localiza????es incompletas ser??o padr??o para \"en\" quando necess??rio. \n"
        "Informe as inst??ncias de strings incorretas para a equipe do Tidy. \n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,                            0,        
        "\n"
        "Se o Tidy for capaz de determinar sua localidade, o Tidy usar?? \n"
        "o idioma da localidade automaticamente. Por exemplo, os sistemas \n"
        "tipo Unix usam uma vari??vel de ambiente $LANG e/ou $LC_ALL. \n"
        "Consulte a documenta????o de seu sistema operacional para obter \n"
        "mais informa????es. \n"
        "\n"
        "Tidy est?? usando a localidade %s. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,                        0, NULL
    }

}};


#endif /* language_pt_br_h */

