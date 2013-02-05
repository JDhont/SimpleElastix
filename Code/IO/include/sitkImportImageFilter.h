/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkImportImageFilter_h
#define __sitkImportImageFilter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /** \class ImportImageFilter
     * \brief Compose a 2D or 3D image and return a smart pointer to a SimpleITK
     * image
     *
     * This filter is intended to interface SimpleITK to other image processing
     * libraries and applications that may have their own representation of an
     * image class.
     *
     * \sa itk::simple::ImportAsInt8, itk::simple::ImportAsUInt8,
     * itk::simple::ImportAsInt16, itk::simple::ImportAsUInt16,
     * itk::simple::ImportAsInt32, itk::simple::ImportAsUInt32,
     * itk::simple::ImportAsInt64, itk::simple::ImportAsUInt64,
     * itk::simple::ImportAsFloat,itk::simple::ImportAsDouble for the
     * procedural interfaces.
     */
    class SITKIO_EXPORT ImportImageFilter
      : public ImageReaderBase {
    public:
      typedef ImportImageFilter Self;

      ImportImageFilter();

      Self& SetSize( const std::vector< unsigned int > &size );
      const std::vector< unsigned int > &GetSize( ) const;

      Self& SetSpacing( const std::vector< double > &spacing );
      const std::vector< double > &GetSpacing( ) const;

      Self& SetOrigin( const std::vector< double > &origin );
      const std::vector< double > &GetOrigin( ) const;

      Self& SetDirection( const std::vector< double > &direction );
      const std::vector< double > &GetDirection( ) const;

      Self& SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt8( uint8_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsInt16( int16_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt16( uint16_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsInt32( int32_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsUInt32( uint32_t * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsFloat( float * buffer, unsigned int numberOfComponents = 1 );
      Self& SetBufferAsDouble( double * buffer, unsigned int numberOfComponents = 1 );

      std::string ToString() const;

      Image Execute();

    protected:

      // Internal method called the the template dispatch system
      template <class TImageType> Image ExecuteInternal ( void );

      // If the output image type is a VectorImage then the number of
      // components per pixel needs to be set, otherwise the method
      // does not exist. This is done with the EnableIf Idiom.
      template <class TImageType>
      typename DisableIf<IsVector<TImageType>::Value>::Type
      SetNumberOfComponentsOnImage( TImageType* ) {}
      template <class TImageType>
      typename EnableIf<IsVector<TImageType>::Value>::Type
      SetNumberOfComponentsOnImage( TImageType* );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( void );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      unsigned int     m_NumberOfComponentsPerPixel;
      PixelIDValueType m_PixelIDValue;

      std::vector< double >         m_Origin;
      std::vector< double >         m_Spacing;
      std::vector< unsigned int >   m_Size;
      std::vector< double >         m_Direction;

      void        * m_Buffer;

    };

  Image SITKIO_EXPORT ImportAsInt8(
    int8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt8(
    uint8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsInt16(
    int16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt16(
    uint16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsInt32(
    int32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsUInt32(
    uint32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsFloat(
    float * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  Image SITKIO_EXPORT ImportAsDouble(
    double * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing = std::vector< double >( 3, 1.0 ),
    const std::vector< double > &origin = std::vector< double >( 3, 0.0 ),
    const std::vector< double > &direction = std::vector< double >(),
    unsigned int numberOfComponents = 1
    );

  }
}

#endif
